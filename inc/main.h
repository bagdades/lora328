#ifndef  MAIN_INC
#define  MAIN_INC

/* #define OW_SENSORS		 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "lmic.h"
#include "hal.h"
#include "config.h"

/* #ifdef  OW_SENSORS */
#include "ds18x20.h"
#include "onewire.h"
/* #endif     #<{(| -----  not OW_SENSORS  ----- |)}># */


/* #ifdef  GPS_TRECKER */
#include "gps.h"
/* #endif     #<{(| -----  not GPS_TRECKER  ----- |)}># */


//Protorypes
static void reportfunc (osjob_t* j);

#endif   /* ----- #ifndef MAIN_INC  ----- */

