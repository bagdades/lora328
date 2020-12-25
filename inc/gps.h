#ifndef  GPS_INC
#define  GPS_INC

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "hal.h"
#include "oslmic.h"

#define 	RX_BUF			100

#define 	TIME_BUF		6
#define 	LATITUDE_BUF	6
#define 	LONGITUDE_BUF	7
#define 	SATELITE_BUF	2
#define 	HEIGHT_BUF		4

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

#endif   /* ----- #ifndef GPS_INC  ----- */
