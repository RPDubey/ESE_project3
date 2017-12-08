/*
 * spi.h
 *
 *  Created on: Dec 4, 2017
 *      Author: Ravi
 */

#ifndef SOURCE_SPI_H_
#define SOURCE_SPI_H_

#include<stdlib.h>

/********************************************************************************
@brief:InitializestheSPIcontroller

InitializestheSPIcontroller
@param:NONE
@return:NONE
********************************************************************************/
void SPI_init();

/********************************************************************************
@brief:Reads a single byte from the SPI bus

Reads a single byte from the SPI
bus@param:uint8_t type read byte
@return:NONE
********************************************************************************/
void SPI_read_byte(uint8_t *byte);

/********************************************************************************
@brief:oSends a singlebyte on the SPI bus

oSends a singlebyte on the SPI bus
@param:uint8_t type byte to send
@return:NONE
********************************************************************************/
void SPI_write_byte(uint8_t byte);


/********************************************************************************
@brief:write multiple data on SPI

Sends numerous SPI Bytes given a pointer to a byte array and a length of how many
bytes to send.
@param:uint8_t* pointer to byte array and it's length
@return:NONE
********************************************************************************/
void SPI_send_packet(uint8_t* p,size_t length);


/********************************************************************************
@brief:Writes out all data on the buffer on SPI

Blocks until SPI transmit buffer has completed transmitting
@param:NONE
@return:NONE
********************************************************************************/

void SPI_flush();



#endif /* SOURCE_SPI_H_ */
