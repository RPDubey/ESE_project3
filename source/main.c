/*******************************************************************************
@file:systick.c
@brief:function declaration for systick configuration

This file declares systick config function
to another
@author:Ravi Dubey
@date:12/1/2017
*******************************************************************************/
#define project3

#include"project3.c"
#include"spi.h"
#include"gpio.h"
#include"nordic.h"

//#define delay_us(i) while(i){i--;}



int main(void){

	GPIO_nrf_init();
	SPI_init();

	delay_us(100);


	//volatile
	uint8_t read[10] ;
	uint8_t addr[5];
uint8_t write_addr[5] ={1,2,3,4,5};

read[0] = nrf_read_config();

read[1] = nrf_read_status();

nrf_write_config(0x01);

read[2] = nrf_read_config();

read[3] = nrf_read_rf_setup();

nrf_write_rf_setup(0x01);

read[4] = nrf_read_config();

read[5] = nrf_read_rf_ch();

nrf_write_rf_ch(0x01);

read[6] = nrf_read_rf_ch();

nrf_read_TX_ADDR(addr);

nrf_write_TX_ADDR(write_addr);

nrf_read_TX_ADDR(addr);

read[0] = nrf_read_fifo_status();


delay_us(1000);

	while(1);

#ifdef project3
//project_3() ;
#endif

}



