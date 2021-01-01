/*
 * =====================================================================================
 *
 *       Filename:  parser.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/01/21 10:25:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  vovan (), volodumurkoval0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "gps.h"


extern uint8_t mode_work; /* 0 - ds18b20, 1 - gpstracker */
extern uint8_t activat_method; /* 0 - ABP, 1 - OTTA */
extern uint8_t EEMEM eep_mode_work;
extern uint8_t EEMEM eep_act_method;

const char PROGMEM modestr[] = "Mode = ";

uint8_t data_count = 0;
char data_in[8];
char command_in[100];
int variable_A = 23;
int variable_goto = 12;
static uint8_t usart_rx_buffer[USART_RX_BUFFER_SIZE];
static volatile uint8_t rx_tailbuffer;
static volatile uint8_t rx_headbuffer;
static volatile uint8_t rx_countbuffer;
static volatile uint8_t idx;
osjob_t process_data;

/* --------------------------------------------------------------------------*/
/**
* @brief search separator in buffer
*
* @param sep
* @param buf
* @param size_buf
* @param start_pos
*
* @return index after separator
*/
/* ----------------------------------------------------------------------------*/
static uint8_t search_sep(uint8_t sep, uint8_t* buf, uint8_t size_buf, uint8_t start_pos)
{
	uint8_t s_pos = start_pos;
	while(buf[s_pos] != sep && s_pos < size_buf) s_pos++;
	s_pos++;
	return s_pos;
}

/* --------------------------------------------------------------------------*/
/**
* @brief copy patch from input buffer to outbuffer
*
* @param in_buf
* @param in_idx
* @param sep
* @param out_buf
* @param size_outBuf
*
* @return  index of buffer
*/
/* ----------------------------------------------------------------------------*/
static uint8_t copy_buf(uint8_t* in_buf, uint8_t in_idx, uint8_t sep, uint8_t* out_buf, uint8_t size_outBuf)
{
	uint8_t idx = in_idx;
	uint8_t i;
	for (i = 0; i < size_outBuf && in_buf[idx] != sep; i++) {
		if(in_buf[idx] == '.') {idx++; i--; continue;}
		/* out_buf[i] = in_buf[idx]; */
		out_buf[i] = in_buf[idx] & 0x0F;
		idx++;
	}
	return idx;
}

void change_sep(uint8_t* buf, uint8_t sep, uint8_t buf_size)
{
	uint8_t i;
	for (i = 0; i < buf_size; i++) {
		if(buf[i] == sep)
			buf[i] = ' ';
	}
}

uint8_t strn_cmp(char* s1, char* s2, uint8_t len)
{
	uint8_t i;
	for (i = 0; i < len; i++) {
		if(s1[i] != s2[i])
			break;
	}
	return len - i;
}

void print_value (char *id, int value) {
  char buffer[8];
  itoa(value, buffer, 10);
  usart_putstr(id);
  usart_putchar('=');
  usart_putstr(buffer);
  usart_putstr(RETURN_NEWLINE);
}

void uart_ok() {
  usart_putstr("OK");
  usart_putstr(RETURN_NEWLINE);
}

void oktet_str(uint8_t b)
{
	usart_putchar("0123456789ABCDEF"[b]);
}

void u1str(uint8_t b)
{
	oktet_str(b >> 4);
	oktet_str(b & 0x0F);
}

void u4t_str(u4_t b)
{
	u1str(b >> 24);
	usart_putchar(' ');
	u1str(b >> 16);
	usart_putchar(' ');
	u1str(b >> 8);
	usart_putchar(' ');
	u1str(b);
}

void key8str(char* buff)
{
	uint8_t i;
	uint8_t j = 7;
	for (i = 0; i < 8; i++) {
		data_in[i] = buff[j];
		j--;
	}
	for (i = 0; i < 8; i++) {
		u1str(data_in[i]);
		usart_putchar(' ');
	}
}

void key16str(char* buff)
{
	uint8_t i;
	for (i = 0; i < 16; i++) {
		u1str(buff[i]);
		usart_putchar(' ');
	}
}

static void copy_command(void)
{
	memcpy(command_in, usart_rx_buffer, 100);
}

static void process_command(void)
{
	if (strcasestr(command_in, "$CFG") != NULL) 
	{
		if(strcasestr(command_in, "?") != NULL)
		{
			usart_putstr("Actvation = ");
			activat_method ? usart_putstr("OTTA") : usart_putstr("ABP");
			usart_putstr(RETURN_NEWLINE);
			usart_putstrP(modestr);
			mode_work ? usart_putstr("GPS") : usart_putstr("DS18B20");
			usart_putstr(RETURN_NEWLINE);
			if (activat_method == ABP_METHOD) 
			{
				u4_t devadd;
				os_getDevAddr(&devadd);
				usart_putstr("DevAddr = ");
				u4t_str(devadd);
				usart_putstr(RETURN_NEWLINE);
				os_getArtEui((uint8_t*)command_in);
				usart_putstr("AppEui = ");
				key8str(command_in);
				usart_putstr(RETURN_NEWLINE);
				os_getDevEui((uint8_t*)command_in);
				usart_putstr("DevEui = ");
				key8str(command_in);
				usart_putstr(RETURN_NEWLINE);
				os_getNwksKey((uint8_t*)command_in);
				usart_putstr("NwksKey = ");
				key16str(command_in);
				usart_putstr(RETURN_NEWLINE);
				os_getAppsKey((uint8_t*)command_in);
				usart_putstr("AppsKey = ");
				key16str(command_in);
				usart_putstr(RETURN_NEWLINE);
			}
			else {
				os_getArtEui((uint8_t*)command_in);
				usart_putstr("AppEui = ");
				key8str(command_in);
				usart_putstr(RETURN_NEWLINE);
				os_getDevEui((uint8_t*)command_in);
				usart_putstr("DevEui = ");
				key8str(command_in);
				usart_putstr(RETURN_NEWLINE);
				os_getDevKey((uint8_t*)command_in);
				usart_putstr("DevKey = ");
				key8str(command_in);
				usart_putstr(RETURN_NEWLINE);
			}
		}
		else if(strcasestr(command_in, "+") != NULL)
		{
			if (strcasestr(command_in, "MODW") != NULL)
			{
				if (strcasestr(command_in, "DS18B20") != NULL)
				{
					eeprom_write_byte(&eep_mode_work, DS18B20_MODE);
					_delay_ms(3);
					uart_ok();
				}
				else if (strcasestr(command_in, "GPS") != NULL)
				{
					eeprom_write_byte(&eep_mode_work, GPS_TRECKER_MODE);
					_delay_ms(3);
					uart_ok();
				}
			}
		}
	}
}

void process_uart(osjob_t* j)
{
	uint8_t i = 0;
	uint8_t sep = ',';
	if(strcasestr((char*)usart_rx_buffer, "$gpgga"))
	{
		memset(data_gps.num_satelites, 0, SATELITE_BUF);
		memset(data_gps.longitude, 0, LONGITUDE_BUF);
		memset(data_gps.latitude, 0, LATITUDE_BUF);
		data_gps.dir_latit = 0;
		data_gps.dir_longit = 0;
		data_gps.quality = 0;
		i = search_sep(sep, usart_rx_buffer, USART_RX_BUFFER_SIZE, i);
		i = copy_buf(usart_rx_buffer, i, sep, (uint8_t*)&data_gps.time, TIME_BUF);
		i = search_sep(sep, usart_rx_buffer, USART_RX_BUFFER_SIZE, i);
		i = copy_buf(usart_rx_buffer, i, sep, (uint8_t*)&data_gps.latitude, LATITUDE_BUF);
		i = search_sep(sep, usart_rx_buffer, USART_RX_BUFFER_SIZE, i);
		if(usart_rx_buffer[i] != sep) data_gps.dir_latit = usart_rx_buffer[i];
		i = search_sep(sep, usart_rx_buffer, USART_RX_BUFFER_SIZE, i);
		i = copy_buf(usart_rx_buffer, i, sep, (uint8_t*)&data_gps.longitude, LONGITUDE_BUF);
		i = search_sep(sep, usart_rx_buffer, USART_RX_BUFFER_SIZE, i);
		if(usart_rx_buffer[i] != sep) data_gps.dir_longit = usart_rx_buffer[i];
		i = search_sep(sep, usart_rx_buffer, USART_RX_BUFFER_SIZE, i);
		if(usart_rx_buffer[i] != sep) data_gps.quality = usart_rx_buffer[i] & 0x0F;
		i = search_sep(sep, usart_rx_buffer, USART_RX_BUFFER_SIZE, i);
		i = copy_buf(usart_rx_buffer, i, sep, (uint8_t*)&data_gps.num_satelites, SATELITE_BUF);
		i = search_sep(sep, usart_rx_buffer, USART_RX_BUFFER_SIZE, i);
		i = copy_buf(usart_rx_buffer, i, sep, (uint8_t*)&data_gps.height, HEIGHT_BUF);
		change_sep((uint8_t*)usart_rx_buffer, ',', USART_RX_BUFFER_SIZE);
	}
	else if(strcasestr((char*)usart_rx_buffer, "$cfg"))
	{
		copy_command();
		process_command();
	}
		/* usart_putstr("CFG\r\n"); */
	UCSR0B |= (1 << RXCIE0);
}

ISR(USART_RX_vect)
{
	uint8_t ch = UDR0;
	usart_rx_buffer[idx] = ch;
	if (usart_rx_buffer[idx] == '\r' || usart_rx_buffer[idx] == '\n') 
	{
		if(usart_rx_buffer[0] != '\n')
		{
			idx = 0;
			UCSR0B &= ~(1 << RXCIE0);
			os_setCallback(&process_data, process_uart);
		}
	}
	else 
	{
		idx++;
		if(idx == USART_RX_BUFFER_SIZE) idx = 0;
	}
}

