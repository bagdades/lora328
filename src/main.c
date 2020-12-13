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

static void initfunc (osjob_t* j) {
	LMIC_reset();
	LMIC_startJoining();
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
	os_setTimedCallback(&tikjob, os_getTime() + ms2osticks(500), tikfunc);
}

void onEvent(ev_t ev)
{
	switch (ev) 
	{
		case EV_JOINING:
			os_setCallback(&tikjob, tikfunc);
			break;
		case EV_JOINED:
			os_clearCallback(&tikjob);	
			PORTC |= (1 << 1);
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

