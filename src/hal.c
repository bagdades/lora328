/*
 * =====================================================================================
 *
 *       Filename:  hal.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01.12.20 22:19:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  vovan (), volodumurkoval0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "hal.h"

u4_t hal_time;
static uint8_t usart_tx_buffer[USART_RX_BUFFER_SIZE];
static volatile uint8_t tx_tailbuffer;
static volatile uint8_t tx_headbuffer;
static volatile uint8_t tx_countbuffer;

/* static int uart_putchar(char c, FILE *stream); */
/* static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE); */
/*  */
/* static int uart_putchar(char c, FILE *stream) */
/* { */
/* 	usart_putchar(c); */
/* 	return 0; */
/* } */

void usart_init(void)
{
	cli();
	//Set baudrate
	UBRR0L = (uint8_t)(BAUD_PRESCALLE & 0xFF);
	UBRR0H = (uint8_t)(BAUD_PRESCALLE >> 8);
	//Enable TX
	UCSR0B |= (1 << TXEN0);
	//Enable RX
	UCSR0B |= (1 << RXEN0);
	//Enable TX interrupt
	UCSR0B |= (1 << TXCIE0);
	//Set frame format to 8 data bits, no parity, 1 stop bit
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	/* stdout = &mystdout; */
	sei();
}

void usart_putchar(uint8_t ch)
{
	if (bit_is_set(UCSR0A, UDRE0) && tx_countbuffer == 0) 
		UDR0 = ch;
	else if (tx_countbuffer < USART_RX_BUFFER_SIZE) 
	{
		tx_countbuffer++;
		usart_tx_buffer[tx_headbuffer] = ch;
		tx_headbuffer++;
		if(tx_headbuffer == USART_TX_BUFFER_SIZE)
			tx_headbuffer = 0;
	}
}

void usart_putstr(char* str)
{
	while (*str) 
	{
		usart_putchar(*str);
		str++;
	}
}

void spi_init(void)
{
	NSS_DDR |= (1 << NSS_PIN);//Port out
	SPI_DDR |= (1 << SPI_MOSI) | (1 << SPI_SCK);
	SPI_DDR &= ~(1 << SPI_MISO);
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0); // Enable SPI, mode master, boud f_osc/16
}

void hal_init (void)
{
	LED_DDR |= (1 << LED_PIN);
	LED_PORT &= ~(1 << LED_PIN);
	usart_init();
	spi_init();
	//Set timer1 
	TCCR0B = (1 << CS02); //Set clock source clkio/256
	TIMSK0 = (1 << TOIE0); //Enable overflow interrupt
	//Int0
	EICRA |= (1 << ISC01) | ( 1 << ISC00);// Int0 rising edge
	EIMSK |= (1 << INT0); //Enable interrupt int0
	//Int PCI
	DDRD &= ~(1 << PORTD5);
	PORTD &= ~(1 << PORTD5);
	PCICR |= (1 << PCIE2);
	PCMSK0 |= (1 << PCINT2);
	set_sleep_mode(SLEEP_MODE_IDLE);
	sei();
}

/*
 * drive radio NSS pin (0=low, 1=high).
 */
void hal_pin_nss (u1_t val)
{
	if(val ==1)
		NSS_PORT |= (1 << NSS_PIN);
	else NSS_PORT &= ~(1 << NSS_PIN);
}

// val ==1  => tx 1, rx 0 ; val == 0 => tx 0, rx 1
void hal_pin_rxtx (u1_t val)
{
#ifdef RX_GPIO_Port
  #ifdef TX_GPIO_Port
  #endif
#endif
}

/*
 * control radio RST pin (0=low, 1=high, 2=floating)
 */
void hal_pin_rst (u1_t val)
{
	if (val == 0 || val == 1) 
	{
		RST_DDR |= (1 << RST_PIN);//Port out
		if (val == 1) 
			RST_PORT |= (1 << RST_PIN);
		else RST_PORT &= ~(1 << RST_PIN);
	}
	else RST_DDR &= ~(1 << RST_PIN);//floating
}

/*
 * perform 8-bit SPI transaction with radio.
 *   - write given byte 'outval'
 *   - read byte and return value
 */
u1_t hal_spi (u1_t outval)
{
	u1_t ret;
	SPDR = outval;
	while (!(SPSR & (1 << SPIF)));
		ret = SPDR;
	return ret;
}
static void hal_spi_trx(u1_t cmd, u1_t* buf, size_t len, bit_t is_read) 
{
	hal_pin_nss(0);
	hal_spi(cmd);
    for (; len > 0; --len, ++buf) {
        u1_t data = is_read ? 0x00 : *buf;
        data = hal_spi(data);
        if (is_read)
            *buf = data;
    }
	hal_pin_nss(1);
}

void hal_spi_write(u1_t cmd, const u1_t* buf, size_t len)
{
	hal_spi_trx(cmd, (u1_t*)buf, len, 0);
}

void hal_spi_read(u1_t cmd, u1_t* buf, size_t len)
{
	hal_spi_trx(cmd, buf, len, 1);
}

void hal_disableIRQs (void)
{
	cli();
}

void hal_enableIRQs (void)
{
	sei();
}

void hal_sleep (void)
{
	asm("sleep");
}

u4_t hal_ticks (void)
{
	cli();
	u4_t t = hal_time;
	u1_t cnt = TCNT0;
	sei();
	return (t << 8) | cnt;
}


// return modified delta ticks from now to specified ticktime (0 for past, FFFF for far future)
static u2_t deltaticks (u4_t time) {
    u4_t t = hal_ticks();
    s4_t d = time - t;
    if( d<=0 ) return 0;    // in the past
    if( (d>>16)!=0 ) return 0xFFFF; // far ahead
    return (u2_t)d;
}

void hal_waitUntil (u4_t time)
{
    while( deltaticks(time) != 0 ); // busy wait until timestamp is reached
}

u2_t hal_checkTimer (u4_t targettime)
{
	u2_t dt;
	if((dt = deltaticks(targettime)) < 5)
		return 1;
	else return 0;
}

void hal_failed (void)
{

}

void hal_deep_sleep (u2_t ticks)
{

}

void hal_deep_sleep4ever (void)
{

}

ISR(TIMER0_OVF_vect)
{
	hal_time++;
}

ISR(USART_TX_vect)
{
	if (tx_countbuffer) 
	{
		UDR0 = usart_tx_buffer[tx_tailbuffer];
		tx_countbuffer--;
		tx_tailbuffer++;
		if(tx_tailbuffer == USART_TX_BUFFER_SIZE)
			tx_tailbuffer = 0;
	}
}

extern void radio_irq_handler(u1_t dio);

ISR(INT0_vect)
{
	/* usart_putstr("Int0\r\n"); */
	radio_irq_handler(0);
}

ISR(PCINT2_vect)
{
	usart_putstr("Int1\r\n");
	if(PIND & (1 << PORTD5))
		radio_irq_handler(1);
}
