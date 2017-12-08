/********************************************************************************
@file:spi.c
@brief:function declarations for SPI library

This file declares functions for SPI library
@author:Ravi Dubey
@date:12/04/2017
 ********************************************************************************/

#include"MKL25Z4.h"
#include"spi.h"
#include<stdlib.h>

void SPI_init(){


	//NVIC
	//NVIC_EnableIRQ(SPI0_IRQn);


	//Set SPI0 to Master & SS pin to auto SS & enable rcv full and tx empty interrupts
	//clock polarity is active high

	SPI0_C1 = SPI_C1_MSTR_MASK ;

	SPI0_C2 &= 0x40;// all zero except the reserved bit

	//Set baud rate prescale divisor to 6 & set baud rate divisor to 8
	SPI0_BR &= 0b11010010;//(SPI_BR_SPPR(0x06) | SPI_BR_SPR(0x08));

	SPI0_C1 |= SPI_C1_SPE_MASK;    //Enable SPI0



}


//void SPI0_IRQHandler(void){
//
//	volatile uint8_t data_send = 8;
//	volatile uint8_t data_rxv;
//
//
//	//check if Rxv buffer full and read the data to clear interrupt
//
//}





void SPI_read_byte(uint8_t* byte){
	while( !(SPI0_S & SPI_S_SPRF_MASK) );
    *byte = SPI0_D;

}

void SPI_write_byte(uint8_t byte){

    while( !(SPI0_S & SPI_S_SPTEF_MASK)  );
    	SPI0_D = byte;

}


void SPI_send_packet(uint8_t* p,size_t length){

	for(size_t i = 0; i< length; i++){

		while( !(SPI0_S & SPI_S_SPTEF_MASK)  );
		    	SPI0_D = *(p+i);
	}
}

void SPI_flush();


