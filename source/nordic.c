/********************************************************************************
@file:nordic.c

@brief:function declarations for nordic library

This file declares functions for nordic library
@author:Ravi Dubey
@date:12/06/2017
 ********************************************************************************/
 #ifdef FRDM
 #include"nordic.h"
 #include"spi.h"
 #include"MKL25Z4.h"
 #endif



#include<stdint.h>
#include"common.h"

#define nrf_chip_enable()
#define nrf_chip_disable()

#define nrf_transmit_enable()       GPIOC_PCOR |= (1UL<<9);
#define nrf_transmit_disable()		GPIOC_PSOR |= (1UL<<9);


uint8_t nrf_read_register(uint8_t reg){

	uint8_t read;

	nrf_transmit_enable();
	SPI_write_byte(R_REGISTER | reg);

	SPI_write_byte(NOP);
	SPI_read_byte(&read);

	SPI_write_byte(NOP);
	SPI_read_byte(&read);

	delay_us(10);
	nrf_transmit_disable();

	return read;

}


void nrf_write_register(uint8_t reg,uint8_t value){

	//uint8_t read;
	nrf_transmit_enable();

	SPI_write_byte( W_REGISTER | reg);
	//SPI_read_byte(&read);

	SPI_write_byte( value);
	//SPI_read_byte(&read);

	delay_us(10);
	nrf_transmit_disable();

}


uint8_t nrf_read_status(){

	return nrf_read_register(STATE);

}


void nrf_write_config(uint8_t config){

	nrf_write_register(CONFIG,config);
}


uint8_t nrf_read_config(){

	return nrf_read_register(CONFIG);

}


uint8_t nrf_read_rf_setup(){

	return nrf_read_register(RF_SETUP);

}

void nrf_write_rf_setup(uint8_t config){

	nrf_write_register(RF_SETUP,config);
}


uint8_t nrf_read_rf_ch(){

	return nrf_read_register(RF_CH);

}


void nrf_write_rf_ch(uint8_t channel){

	nrf_write_register(RF_CH,channel);
}


void nrf_read_TX_ADDR(uint8_t* address){



	nrf_transmit_enable();
	SPI_write_byte(R_REGISTER | TX_ADDR);

	SPI_write_byte(NOP);
	SPI_read_byte(address);

	SPI_write_byte(NOP);
	SPI_read_byte(address);

	SPI_write_byte(NOP);
	SPI_read_byte(address+1);

	SPI_write_byte(NOP);
	SPI_read_byte(address+2);

	SPI_write_byte(NOP);
	SPI_read_byte(address+3);

	SPI_write_byte(NOP);
	SPI_read_byte(address+4);

	delay_us(10);
	nrf_transmit_disable();


}


void nrf_write_TX_ADDR(uint8_t* tx_addr){

	nrf_transmit_enable();

	SPI_write_byte( W_REGISTER | TX_ADDR);

	//curiously, MSB gets written first and then LSB to MSB-1
	SPI_write_byte( *(tx_addr+4));
	SPI_write_byte( *(tx_addr+0));
	SPI_write_byte( *(tx_addr+1));
	SPI_write_byte( *(tx_addr+2));
	SPI_write_byte( *(tx_addr+3));

	delay_us(10);
	nrf_transmit_disable();


}


uint8_t nrf_read_fifo_status(){

	return nrf_read_register(FIFO_STATUS);

}


void nrf_flush_tx_fifo(){

	nrf_transmit_enable();
	SPI_write_byte(FLUSH_TX_FIFO);

	delay_us(10);
	nrf_transmit_disable();

}


void nrf_flush_rx_fifo(){

	nrf_transmit_enable();
	SPI_write_byte(FLUSH_RX_FIFO);

	delay_us(10);
	nrf_transmit_disable();


}
