/*******************************************************************************
@file:uart.c
@brief:function declarations for uart operation functions
This file declares functions for implementing operations defined in uart.h
@author:Ravi Dubey
@date:10/22/2017
 *******************************************************************************/

#include <stdlib.h>
#include "uart.h"
#include "MKL25Z4.h"

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "pin_mux.h"

//#include "nvic.h"
#define INT_UART0 28

#include "circbuf.h"

extern uint8_t verbose_flag;
CB_t* command_CB;
unsigned_byte newline[2] = "\r\n" ;

return_enum UART_configure(){


	//EnableInterrupts;

	//    enable_irq(INT_UART0 -16);
	//	set_irq_priority((INT_UART0 -16), 2);
	NVIC_EnableIRQ(UART0_IRQn);

	UART0->C2 |= UART_C2_RIE_MASK;
	//	UART0->C2 |= UART_C2_TIE_MASK;

	//two byte CB for run time switch
	command_CB = (CB_t*)(malloc(sizeof(CB_t)));
	CB_init(command_CB,2);




	return 0;
}

return_enum UART_send(unsigned_byte* data_ptr){

	while(!(UART0->S1 & UART0_S1_TDRE_MASK));//wait until Tx Data register is empty
	UART0->D = *data_ptr;
	return 0;
}

return_enum UART_send_n(unsigned_byte* data_ptr,size_t num_bytes){

	if(data_ptr == NULL) return (return_enum)Fail;

	while(num_bytes){

		while(!(UART0->S1 & UART0_S1_TDRE_MASK));//wait until Tx Data register is empty
		UART0->D = *data_ptr;
		data_ptr++;
		num_bytes--;
	}
	return 0;
}

return_enum UART_receive(unsigned_byte* data_ptr){

	while (!(UART0->S1 & UART0_S1_RDRF_MASK));//wait until Rx data register is full
	*data_ptr = UART0->D;
	return 0;
}


return_enum UART_receive_n(unsigned_byte* data_ptr,size_t num_bytes){
	while(num_bytes){

		while (!(UART0->S1 & UART0_S1_RDRF_MASK));//wait until Rx data register is full
		*data_ptr = UART0->D;
		data_ptr++;
		num_bytes--;
	}
	return 0;
}



void UART0_IRQHandler(){


	//if RX interrupt
	if (UART0->S1 & UART_S1_RDRF_MASK)
	{
		UART0->S1 &= ~UART_S1_RDRF_MASK; //clear the Rx interrupt
		//Rx_function();//registered in main
		unsigned_byte data = UART0->D;
		unsigned_byte pop;

		if(CB_is_empty(command_CB) == Buffer_Empty){
			CB_buffer_add_item(command_CB,data);
			UART_send_n(newline,2);
			UART_send(&data);
		}

		else //if this is the second entry
		{
			UART_send(&data);
			CB_buffer_remove_item(command_CB,&pop);

			if( (pop == 'o') && (data == 'n') ){
				verbose_flag = 1;
			}

			if( (pop == 'o') && (data == 'f') ){
				verbose_flag = 0;
			}


		}
	}

	//if TX interrupt
	if ( ((UART0->S1 & UART_S1_TDRE_MASK) || (UART0->S1 & UART_S1_TC_MASK)) )
	{

		UART0->S1 &= ~UART_S1_TDRE_MASK; //clear the Tx interrupt
		//Tx_function();//registered in main
		//		unsigned_byte data = UART0->D;
		//
		//		UART_receive(&data);

	}

}

