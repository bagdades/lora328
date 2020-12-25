/*
 * =====================================================================================
 *
 *       Filename:  gps.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/23/20 19:39:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  vovan (), volodumurkoval0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "gps.h"

static uint8_t buf_rx[RX_BUF];
volatile static uint8_t ind;
osjob_t savedata;

/* --------------------------------------------------------------------------*/
/**
* @brief search separator in buffer
*
* @param sep
* @param buf
* @param size_buf
* @param start_pos
*
* @return index of buffer
*/
/* ----------------------------------------------------------------------------*/
uint8_t search_sep(uint8_t sep, uint8_t* buf, uint8_t size_buf, uint8_t start_pos)
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
* @return  index after separator
*/
/* ----------------------------------------------------------------------------*/
uint8_t copy_buf(uint8_t* in_buf, uint8_t in_idx, uint8_t sep, uint8_t* out_buf, uint8_t size_outBuf)
{
	uint8_t idx = in_idx;
	uint8_t i;
	for (i = 0; i < size_outBuf && in_buf[idx] != sep; i++) {
		if(in_buf[idx] == '.') {idx++; i--; continue;}
		out_buf[i] = in_buf[idx] & 0x0F;
		idx++;
	}
	return idx;
}

static void saveDataBuf(osjob_t* j)
{
	uint8_t i = 0;
	uint8_t sep = ',';
	memset(data_gps.num_satelites, 0, SATELITE_BUF);
	memset(data_gps.longitude, 0, LONGITUDE_BUF);
	memset(data_gps.latitude, 0, LATITUDE_BUF);
	data_gps.dir_latit = 0;
	data_gps.dir_longit = 0;
	data_gps.quality = 0;
	i = search_sep(sep, buf_rx, RX_BUF, i);
	i = copy_buf(buf_rx, i, sep, (uint8_t*)&data_gps.time, TIME_BUF);
	i = search_sep(sep, buf_rx, RX_BUF, i);
	i = copy_buf(buf_rx, i, sep, (uint8_t*)&data_gps.latitude, LATITUDE_BUF);
	i = search_sep(sep, buf_rx, RX_BUF, i);
	if(buf_rx[i] != sep) data_gps.dir_latit = buf_rx[i];
	i = search_sep(sep, buf_rx, RX_BUF, i);
	i = copy_buf(buf_rx, i, sep, (uint8_t*)&data_gps.longitude, LONGITUDE_BUF);
	i = search_sep(sep, buf_rx, RX_BUF, i);
	if(buf_rx[i] != sep) data_gps.dir_longit = buf_rx[i];
	i = search_sep(sep, buf_rx, RX_BUF, i);
	if(buf_rx[i] != sep) data_gps.quality = buf_rx[i] & 0x0F;
	i = search_sep(sep, buf_rx, RX_BUF, i);
	i = copy_buf(buf_rx, i, sep, (uint8_t*)&data_gps.num_satelites, SATELITE_BUF);
	i = search_sep(sep, buf_rx, RX_BUF, i);
	i = copy_buf(buf_rx, i, sep, (uint8_t*)&data_gps.height, HEIGHT_BUF);
	UCSR0B |= (1 << RXCIE0);
}

ISR(USART_RX_vect)
{
	uint8_t ch = UDR0;
	buf_rx[ind] = ch;
	if (ind < 6) 
	{
		if (buf_rx[ind] != "$GPGGA"[ind]) 
			ind = 0;
	}
	if (ind >= 50 || buf_rx[ind] == '\r' || buf_rx[ind] == '\n') 
	{
		ind = 0;
		UCSR0B &= ~(1 << RXCIE0);
		os_setCallback(&savedata, saveDataBuf);
	}
	ind++;
	if(ind >= 99) ind = 0;
}
