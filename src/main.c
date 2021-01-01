/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  30.11.20 23:49:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  vovan (), volodumurkoval0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "main.h"

uint8_t EEMEM eep_mode_work = DS18B20_MODE;;
uint8_t EEMEM eep_act_method;
// ABP
u1_t EEMEM eep_appeui[8];
u1_t EEMEM eep_deveui[8];
u1_t EEMEM eep_nwkskey[16];
u1_t EEMEM eep_appskey[16];
u4_t EEMEM eep_devaddr;

uint8_t mode_work; /* 0 - ds18b20, 1 - gpstracker */
uint8_t activat_method = ABP_METHOD; /* 0 - ABP, 1 - OTTA */


// application router ID (LSBF)  < ------- IMPORTANT
#define ABP
static  u1_t APPEUI[8]  = { 0xD5, 0x73, 0x03, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 };


// unique device ID (LSBF)       < ------- IMPORTANT

#ifdef  ABP
static  u1_t DEVEUI[8]  = { 0x24, 0x2C, 0x70, 0x25, 0xD7, 0x11, 0x09, 0x00 };//ABP
// device-specific AES key (derived from device EUI)
static  u1_t DEVKEY[16] = { 0x17, 0xD1, 0x31, 0x96, 0xDF, 0x02, 0x9C, 0x15, 0x45, 0x0B, 0x5C, 0x50, 0xA0, 0xDD, 0xD9, 0x55 };
#else      /* -----  not ABP  ----- */
static  u1_t DEVEUI[8]  = { 0x77, 0xEC, 0xAC, 0xD3, 0x00, 0xB5, 0xC5, 0x00};//OTTA
#endif     /* -----  not ABP  ----- */



#ifdef  ABP
//   ABP
static  u1_t NWKSKEY[16] = { 0x70, 0x9A, 0x66, 0x6B, 0x26, 0x11, 0x1E, 0x90, 0xDD, 0xD3, 0x7F, 0x4E, 0x59, 0x69, 0x73, 0xB2 };
#endif     /* -----  ABP  ----- */

#ifdef  ABP
static  u1_t APPSKEY[16] = { 0x9E, 0x3B, 0x6E, 0x84, 0x0D, 0xCE, 0xCA, 0x5E, 0x68, 0x85, 0x9B, 0xB9, 0xD0, 0x00, 0x10, 0xEB }; /* ABP */
static  u4_t DEVADDR = 0x260111DF;
#else      /* -----  not ABP  ----- */
static  u1_t DEVKEY[16] = { 0x46, 0xDC, 0x9E, 0x10, 0x3C, 0x79, 0xA3, 0xB1, 0xC6, 0x92, 0x58, 0xD3, 0xCC, 0xE1, 0x3C, 0x98}; /* OTTA */
#endif     /* -----  not ABP  ----- */

static void reporttemp (osjob_t* j);

void os_getNwksKey(u1_t* buf)
{
	memcpy(buf, NWKSKEY, 16);
}

void os_getAppsKey(u1_t* buf)
{
	memcpy(buf, APPSKEY, 16);
}

// provide application router ID (8 bytes, LSBF)
void os_getArtEui (u1_t* buf) {
    memcpy(buf, APPEUI, 8);
}

// provide device ID (8 bytes, LSBF)
void os_getDevEui (u1_t* buf) {
    memcpy(buf, DEVEUI, 8);
}

// provide device key (16 bytes)
void os_getDevKey (u1_t* buf) {
    memcpy(buf, DEVKEY, 16);
}

void os_getDevAddr(u4_t* buf) {
	*buf = DEVADDR;
}

static osjob_t reportjob;

/* #ifdef  OW_SENSORS */
static osjob_t startmeasurejob;

static void  startmeasure(osjob_t* j)
{
	DS18X20_start_meas(DS18X20_POWER_EXTERN, 0);
	os_setTimedCallback(&reportjob, os_getTime() + ms2osticks(750), reporttemp);
}

// report sensor value every minute
static void reporttemp (osjob_t* j) {
	u1_t subzero;
	u1_t cel;
	u1_t cel_frac_bits;
	DS18X20_read_meas_single(DS18B20_ID, &subzero, &cel, &cel_frac_bits);
	// prepare and schedule data for transmission
	/* LMIC.frame[0] = val << 8; */
	/* LMIC.frame[1] = val; */
	LMIC.frame[0] = subzero;
	LMIC.frame[1] = cel;
	LMIC.frame[2] = cel_frac_bits;
	LMIC_setTxData2(1, LMIC.frame, 3, 0); // (port 1, 2 bytes, unconfirmed)
	/* usart_putstr("Report.\r\n"); */
	os_setTimedCallback(&startmeasurejob, os_getTime()+sec2osticks(5), startmeasure);
}

/* #endif     #<{(| -----  not OW_SENSORS  ----- |)}># */


/* #ifdef  GPS_TRECKER */
static void reportfunc(osjob_t* j)
{
	uint32_t res;
	res = ((data_gps.latitude[0] * 10) + data_gps.latitude[1]) * (uint32_t)(10000)
		+ ((data_gps.latitude[2] * 10) + data_gps.latitude[3]) * (uint32_t)(100)
		+ (data_gps.latitude[4] * 10) + data_gps.latitude[5];
	LMIC.frame[0] = (data_gps.time[0] << 4) | (data_gps.time[1] & 0x0F);
	LMIC.frame[1] = (data_gps.time[2] << 4) | (data_gps.time[3] & 0x0F);
	LMIC.frame[2] = (data_gps.time[4] << 4) | (data_gps.time[5] & 0x0F);
	LMIC.frame[3] = res >> 16;
	LMIC.frame[4] = res >> 8;
	LMIC.frame[5] = res;
	LMIC.frame[6] = (data_gps.dir_latit);
	res = ((data_gps.longitude[1] * 10) + data_gps.longitude[2]) * (uint32_t)(10000)
		+ ((data_gps.longitude[3] * 10) + data_gps.longitude[4]) * (uint32_t)(100)
		+ (data_gps.longitude[5] * 10) + data_gps.longitude[6];
	LMIC.frame[7] = res >> 16;
	LMIC.frame[8] = res >> 8;
	LMIC.frame[9] = res;
	LMIC.frame[10] = (data_gps.dir_longit);
	LMIC.frame[11] = (data_gps.quality);
	LMIC.frame[12] = data_gps.num_satelites[0] * 10 + data_gps.num_satelites[1];
	uint16_t hight = ((data_gps.height[0] * 10) + data_gps.height[1]) * 100 +
		(data_gps.height[2] * 10) + data_gps.height[3];
	LMIC.frame[13] = hight >> 8;
	LMIC.frame[14] = hight;
	LMIC_setTxData2(1, LMIC.frame, 15, 0);
	os_setTimedCallback(j, os_getTime() + sec2osticks(10), reportfunc);
}
/* #endif     #<{(| -----  not GPS_TRECKER  ----- |)}># */

static void initfunc (osjob_t* j) {
	LMIC_reset();
	// start joining
	LMIC_startJoining();
	// init done - onEvent() callback will be invoked...

	//   ABP
#ifdef  ABP
	uint8_t appskey[sizeof(APPSKEY)];
	memcpy(appskey, APPSKEY, sizeof(APPSKEY));
	uint8_t nwkskey[sizeof(NWKSKEY)];
	memcpy(nwkskey, NWKSKEY, sizeof(NWKSKEY));
	LMIC_setSession (0x1, DEVADDR, nwkskey, appskey);
#endif     /* -----   ABP  ----- */



#ifdef  ONE_CHANEL
	LMIC_setupChannel(0, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(1, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7B), BAND_CENTI);      // g-band
	LMIC_setupChannel(2, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(3, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(4, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(5, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(6, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(7, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(8, 868800000, DR_RANGE_MAP(DR_FSK,  DR_FSK),  BAND_MILLI);      // g2-band
#else      /* -----  not ONE_CHANEL  ----- */
	LMIC_setupChannel(0, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(1, 868300000, DR_RANGE_MAP(DR_SF12, DR_SF7B), BAND_CENTI);      // g-band
	LMIC_setupChannel(2, 868500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(3, 867100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(4, 867300000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(5, 867500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(6, 867700000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(7, 867900000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(8, 868800000, DR_RANGE_MAP(DR_FSK,  DR_FSK),  BAND_MILLI);      // g2-band
#endif     /* -----  not ONE_CHANEL  ----- */

	// Disable link check validation
	LMIC_setLinkCheckMode(0);
	// TTN uses SF9 for its RX2 window.
	LMIC.dn2Dr = DR_SF9;
	// Set data rate and transmit power for uplink (note: txpow seems to be ignored by the library)
	LMIC_setDrTxpow(DR_SF7,14);

/* #ifdef  GPS_TRECKER */
	if (mode_work == GPS_TRECKER_MODE) 
	{
		os_setTimedCallback(j, os_getTime(), reportfunc);
	}
/* #endif     #<{(| -----  not GPS_TRECKER  ----- |)}># */
	/* os_setTimedCallback(j, os_getTime(), reportfunc); */
}

static osjob_t tikjob;

static void tikfunc(osjob_t* j)
{
	if (LED_PORT & (1 << LED_PIN)) 
	{
		LED_PORT &= ~(1 << LED_PIN);
	}
	else LED_PORT |= (1 << LED_PIN);
	/* _delay_ms(1000); */
	/* os_setCallback(&tikjob, tikfunc); */
	/* printf("Ticks: %lu\r\n", hal_ticks()); */
	os_setTimedCallback(&tikjob, os_getTime() + sec2osticks(1), tikfunc);
}


#ifdef  DEBUG_LOG
void debug_event (int ev) {
    static char* evnames[] = {
        [EV_SCAN_TIMEOUT]   = "SCAN_TIMEOUT",
        [EV_BEACON_FOUND]   = "BEACON_FOUND",
        [EV_BEACON_MISSED]  = "BEACON_MISSED",
        [EV_BEACON_TRACKED] = "BEACON_TRACKED",
        [EV_JOINING]        = "JOINING",
        [EV_JOINED]         = "JOINED",
        [EV_RFU1]           = "RFU1",
        [EV_JOIN_FAILED]    = "JOIN_FAILED",
        [EV_REJOIN_FAILED]  = "REJOIN_FAILED",
        [EV_TXCOMPLETE]     = "TXCOMPLETE",
        [EV_LOST_TSYNC]     = "LOST_TSYNC",
        [EV_RESET]          = "RESET",
        [EV_RXCOMPLETE]     = "RXCOMPLETE",
        [EV_LINK_DEAD]      = "LINK_DEAD",
        [EV_LINK_ALIVE]     = "LINK_ALIVE",
        [EV_SCAN_FOUND]     = "SCAN_FOUND",
        [EV_TXSTART]        = "EV_TXSTART",
    };
    usart_putstr((ev < sizeof(evnames)/sizeof(evnames[0])) ? evnames[ev] : "EV_UNKNOWN" );
    usart_putchar('\r');
    usart_putchar('\n');
}
#endif     /* -----  not DEBUG_LOG  ----- */

void onEvent(ev_t ev)
{

#ifdef  DEBUG_LOG
	debug_event(ev);
#endif     /* -----  DEBUG_LOG  ----- */

	switch(ev) {

		// network joined, session established
		case EV_JOINING:
			/* usart_putstr("try joining\r\n"); */
			break;
		case EV_JOINED:
			/* debug_led(1); */
			// kick-off periodic sensor job
			if (mode_work == GPS_TRECKER_MODE) 
			{
				reportfunc(&reportjob);
			} else if (mode_work == DS18B20_MODE) 
			{
				reporttemp(&reportjob);
			}
			break;
		case EV_JOIN_FAILED:
			/* usart_putstr("join failed\r\n"); */
			break;
		case EV_SCAN_TIMEOUT:
			/* usart_putstr("EV_SCAN_TIMEOUT\r\n"); */
			break;
		case EV_BEACON_FOUND:
			/* usart_putstr("EV_BEACON_FOUND\r\n"); */
			break;
		case EV_BEACON_MISSED:
			/* usart_putstr("EV_BEACON_MISSED\r\n"); */
			break;
		case EV_BEACON_TRACKED:
			/* usart_putstr("EV_BEACON_TRACKED\r\n"); */
			break;
		case EV_RFU1:
			/* usart_putstr("EV_RFU1\r\n"); */
			break;
		case EV_REJOIN_FAILED:
			/* usart_putstr("EV_REJOIN_FAILED\r\n"); */
			break;
		case EV_TXCOMPLETE:
			/* usart_putstr("EV_TXCOMPLETE (includes waiting for RX windows)\r\n"); */
			if (LMIC.txrxFlags & TXRX_ACK)
				/* usart_putstr("Received ack\r\n"); */
			if (LMIC.dataLen) {
				/* usart_putstr("Received "); */
				/* printf("%d", LMIC.dataLen); */
				/* usart_putstr(" bytes of payload\r\n"); */
			}
			break;
		case EV_LOST_TSYNC:
			/* usart_putstr("EV_LOST_TSYNC\r\n"); */
			break;
		case EV_RESET:
			/* usart_putstr("EV_RESET\r\n"); */
			break;
		case EV_RXCOMPLETE:
			// data received in ping slot
			/* usart_putstr("EV_RXCOMPLETE\r\n"); */
			break;
		case EV_LINK_DEAD:
			/* usart_putstr("EV_LINK_DEAD\r\n"); */
			break;
		case EV_LINK_ALIVE:
			/* usart_putstr("EV_LINK_ALIVE\r\n"); */
			break;
		default:
			/* usart_putstr("Unknown event\r\n"); */
			break;
	}
}



int main(void)
{
	osjob_t initjob;
	mode_work = eeprom_read_byte(&eep_mode_work);
	os_init();

/* #ifdef  OW_SENSORS */
	if (mode_work == DS18B20_MODE) 
	{
		ow_init();
		startmeasure(&reportjob);
	}
/* #endif     #<{(| -----  not OW_SENSORS  ----- |)}># */
	usart_putstr("Hello from node.\r\n");
	os_setCallback(&tikjob, tikfunc);
	os_setCallback(&initjob, initfunc);
	os_runloop();
	while (1) 
	{
	}
}

