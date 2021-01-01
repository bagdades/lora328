#ifndef  PARSER_INC
#define  PARSER_INC

#include "hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "config.h"


#define 	TIME_BUF		10
#define 	LATITUDE_BUF	15
#define 	LONGITUDE_BUF	15
#define 	SATELITE_BUF	3
#define 	HEIGHT_BUF		5

#define 	TRUE					1
#define 	FALSE					0
#define 	CHAR_NEWLINE			'\n'
#define 	CHAR_RETURN				'\r'
#define 	RETURN_NEWLINE			"\r\n"

typedef struct 
{
	uint8_t time[TIME_BUF];
	uint8_t latitude[LATITUDE_BUF];
	uint8_t longitude[LONGITUDE_BUF];
	uint8_t dir_latit;
	uint8_t dir_longit;
	uint8_t quality;
	uint8_t num_satelites[SATELITE_BUF];
	uint8_t height[HEIGHT_BUF];
}GPS_t;

GPS_t data_gps;

//Prototypes
void process_uart(osjob_t* j);
uint16_t usart_getchar(void);

#endif   /* ----- #ifndef PARSER_INC  ----- */
