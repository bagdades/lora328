/*
 * Copyright (c) 2014-2016 IBM Corporation.
 * All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of the <organization> nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _hal_hpp_
#define _hal_hpp_

#include "oslmic.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
/* #include <stdio.h> */
#include "printf-stdarg.h"
#include "lmic.h"

#define LED_PORT				PORTC
#define LED_DDR					DDRC
#define LED_PIN					PORTC1

//Uart
#define F_CPU					8000000UL
#define USART_BAUDRATE			9600
#define BAUD_PRESCALLE			(((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define USART_TX_BUFFER_SIZE	20
#define USART_RX_BUFFER_SIZE	20

//Spi
#define NSS_PORT	PORTB
#define RST_PORT	PORTB
#define NSS_DDR		DDRB
#define RST_DDR		DDRB
#define NSS_PIN		PORTB2
#define RST_PIN		PORTB1
#define SPI_PORT	PORTB
#define SPI_DDR		DDRB
#define SPI_MOSI	PORTB3
#define SPI_MISO	PORTB4
#define SPI_SCK		PORTB5

/* represent the various radio TX power policy */
enum	{
	LMICHAL_radio_tx_power_policy_rfo	= 0,
	LMICHAL_radio_tx_power_policy_paboost	= 1,
	LMICHAL_radio_tx_power_policy_20dBm	= 2,
};

/* 
 * initialize spi
 */
void spi_init(void);


/* 
 * initialize uart
 */
void usart_init(void);

/* 
 * uart transmit
 */
void usart_putchar(uint8_t ch);

/* 
 *uart put string
 */
void usart_putstr(char* str);

/*
 * initialize hardware (IO, SPI, TIMER, IRQ).
 */
void hal_init (void);

/*
 * drive radio NSS pin (0=low, 1=high).
 */
void hal_pin_nss (u1_t val);

/*
 * drive radio RX/TX pins (0=rx, 1=tx).
 */
void hal_pin_rxtx (u1_t val);

/*
 * control radio RST pin (0=low, 1=high, 2=floating)
 */
void hal_pin_rst (u1_t val);

/*
 * perform 8-bit SPI transaction with radio.
 *   - write given byte 'outval'
 *   - read byte and return value
 */
u1_t hal_spi (u1_t outval);

/*
 * disable all CPU interrupts.
 *   - might be invoked nested 
 *   - will be followed by matching call to hal_enableIRQs()
 */
void hal_disableIRQs (void);

/*
 * enable CPU interrupts.
 */
void hal_enableIRQs (void);

/*
 * put system and CPU in low-power mode, sleep until interrupt.
 */
void hal_sleep (void);

/*
 * return 32-bit system time in ticks.
 */
u4_t hal_ticks (void);

/*
 * busy-wait until specified timestamp (in ticks) is reached.
 */
void hal_waitUntil (u4_t time);

/*
 * check and rewind timer for target time.
 *   - return 0 if target time is close or very close, a few ticks ahead
 *   - otherwise rewind timer for target time or full period and return ticks until timeout (>0 && <= 0xffff)
 */
u2_t hal_checkTimer (u4_t targettime);

/*
 * perform fatal failure action.
 *   - called by assertions
 *   - action could be HALT or reboot
 */
void hal_failed (void);



/*
 * put system and CPU in low-power mode, pass on ticks until timer interrupt is expected.
 */
void hal_deep_sleep (u2_t ticks);



/*
 * put system and CPU in low-power mode, sleep until interrupt.
 */
void hal_deep_sleep4ever (void);

/*
 * Perform SPI write transaction with radio chip
 *   - write the command byte 'cmd'
 *   - write 'len' bytes out of 'buf'
 */
void hal_spi_write(u1_t cmd, const u1_t* buf, size_t len);

/*
 * Perform SPI read transaction with radio chip
 *   - write the command byte 'cmd'
 *   - read 'len' bytes into 'buf'
 */
void hal_spi_read(u1_t cmd, u1_t* buf, size_t len);



#endif // _hal_hpp_
