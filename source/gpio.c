/********************************************************************************
@file:gpio.c
@brief:function declarations for gpio initiations

This file declares functions for initiating gpio pins associated with SPI and NRF
devices
@author:Ravi Dubey
@date:12/04/2017
 ********************************************************************************/
#include"MKL25Z4.h"
#include"common.h"
#include"gpio.h"
#include<stdint.h>
void GPIO_nrf_init(void){


	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;      	//Turn on clock to C port
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;       	//Enable SPI0 clock



	//PTC9 is the slave select pin
	PORTC_PCR9 = PORT_PCR_MUX(0x1);    			//Set PTC9 as GPIO (alternative 1)
	GPIOC_PDDR |= (1UL<<9);//configure the pin as output
	GPIOC_PSOR |= (1UL<<9);//default on, slave not selected


	//PTC11 as the chip enable nordic. Should be high.
	PORTC_PCR11 = PORT_PCR_MUX(0x1);    			//Set PTC11 as GPIO (alternative 1)
	GPIOC_PDDR |= (1UL<<11);//configure the pin as output
	GPIOC_PSOR |= (1UL<<11);//on for chip enable



	//	PORTC_PCR4 = PORT_PCR_MUX(0x2);    			//Set PTC4 to mux 2 [SPI0_PCS0]
	PORTC_PCR5 = PORT_PCR_MUX(0x2);   			//Set PTC5 to mux 2 [SPI0_SCK]
	PORTC_PCR6 = PORT_PCR_MUX(0x2);    			//Set PTC6 to mux 2 [SPI0_MOSI]
	PORTC_PCR7 = PORT_PCR_MUX(0x2);    			//Set PTC7 to mux 2 [SPIO_MISO]


}
