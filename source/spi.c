/********************************************************************************
@file:spi.c
@brief:function declarations for SPI library

This file declares functions for SPI library
@author:Ravi Dubey
@date:12/04/2017
********************************************************************************/


void SPI_init();

void SPI_read_byte(uint8_t byte);

void SPI_write_byte(uint8_t byte);


void SPI_send_packet(uint8_* p,size_t length);

void SPI_flush();


