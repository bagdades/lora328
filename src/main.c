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


// application router ID (LSBF)  < ------- IMPORTANT
static  u1_t APPEUI[8]  = { 0xD5, 0x73, 0x03, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 };
// unique device ID (LSBF)       < ------- IMPORTANT
static  u1_t DEVEUI[8]  = { 0x24, 0x2C, 0x70, 0x25, 0xD7, 0x11, 0x09, 0x00 };

// device-specific AES key (derived from device EUI)
static  u1_t DEVKEY[16] = { 0x17, 0xD1, 0x31, 0x96, 0xDF, 0x02, 0x9C, 0x15, 0x45, 0x0B, 0x5C, 0x50, 0xA0, 0xDD, 0xD9, 0x55 };

//   ABP
static  u1_t NWKSKEY[16] = { 0x70, 0x9A, 0x66, 0x6B, 0x26, 0x11, 0x1E, 0x90, 0xDD, 0xD3, 0x7F, 0x4E, 0x59, 0x69, 0x73, 0xB2 };
static  u1_t APPSKEY[16] = { 0x9E, 0x3B, 0x6E, 0x84, 0x0D, 0xCE, 0xCA, 0x5E, 0x68, 0x85, 0x9B, 0xB9, 0xD0, 0x00, 0x10, 0xEB };
static  u4_t DEVADDR = 0x260111DF;

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

u2_t readsensor(){
	u2_t value = 0xAA;    /// read from evrything ...make your own sensor
	return value;
}

static osjob_t reportjob;

// report sensor value every minute
static void reportfunc (osjob_t* j) {
	  // read sensor
	    u2_t val = readsensor();
	    // prepare and schedule data for transmission
	    LMIC.frame[0] = val << 8;
	    LMIC.frame[1] = val;
	    LMIC_setTxData2(1, LMIC.frame, 2, 0); // (port 1, 2 bytes, unconfirmed)
		/* usart_putstr("Report.\r\n"); */
	    os_setTimedCallback(j, os_getTime()+sec2osticks(5), reportfunc);
}

static void initfunc (osjob_t* j) {
	LMIC_reset();
	// start joining
	LMIC_startJoining();
	// init done - onEvent() callback will be invoked...

	//   ABP
	uint8_t appskey[sizeof(APPSKEY)];
	uint8_t nwkskey[sizeof(NWKSKEY)];
	memcpy(appskey, APPSKEY, sizeof(APPSKEY));
	memcpy(nwkskey, NWKSKEY, sizeof(NWKSKEY));
	LMIC_setSession (0x1, DEVADDR, nwkskey, appskey);

	LMIC_setupChannel(0, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(1, 868300000, DR_RANGE_MAP(DR_SF12, DR_SF7B), BAND_CENTI);      // g-band
	LMIC_setupChannel(2, 868500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(3, 867100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(4, 867300000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(5, 867500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(6, 867700000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(7, 867900000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
	LMIC_setupChannel(8, 868800000, DR_RANGE_MAP(DR_FSK,  DR_FSK),  BAND_MILLI);      // g2-band

	// Disable link check validation
	LMIC_setLinkCheckMode(0);
	// TTN uses SF9 for its RX2 window.
	LMIC.dn2Dr = DR_SF9;
	// Set data rate and transmit power for uplink (note: txpow seems to be ignored by the library)
	LMIC_setDrTxpow(DR_SF7,14);

	os_setTimedCallback(j, os_getTime(), reportfunc);
}

osjob_t tikjob;

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

void onEvent(ev_t ev)
{
	debug_event(ev);
	switch(ev) {

		// network joined, session established
		case EV_JOINING:
			/* usart_putstr("try joining\r\n"); */
			break;
		case EV_JOINED:
			/* debug_led(1); */
			// kick-off periodic sensor job
			reportfunc(&reportjob);
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
	os_init();
	usart_putstr("Hello from node.\r\n");
	os_setCallback(&tikjob, tikfunc);
	os_setCallback(&initjob, initfunc);
	os_runloop();
	while (1) 
	{
	}
}

