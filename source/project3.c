/*******************************************************************************
@file:project3.c
@brief:project3 functions

This file initializes all the functionality for project3
@author:Ravi Dubey
@date:12/1/2017
*******************************************************************************/
#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"pin_mux.c"
#include"clock_config.c"
#include "board.h"
#include"dma_memory.h"
#include"memory.h"
#include"systick.h"
#include"circbuf.h"
#include"uart.h"
#include"logger_que.h"
#include "RTC.h"
#include"common.h"


#define VERBOSE
#define len 5000


LQ_t*__attribute__((section (".buffer"))) LQ_buf_ptr;
extern log_data_struct heartbeat_data;
log_data_struct out_data;
extern uint8_t heartbeat_flag;

void clock_config(void);

void project_3(void);

void project_3(void){
BOARD_InitPins();
clock_config();

//#ifdef profiling
//uint8_t source[len];
//uint8_t dst[len];
//uint16_t i =0;
//
//for (i=0;i<len;i++){
//	source[i] = 1;
//	dst[i] = 0;
//}
//
////set up for profiling
//volatile uint32_t start_ticks = 0;
//volatile uint32_t end_ticks = 0;
//volatile uint32_t time_us = 0;
//
//Systick_config();
//
//start_ticks = usec_count;
////memset(dst,len,1);
// //my_memset(dst,len,1);
////memset_dma(dst,len,1);
//memmove_dma(source,dst,len);
//end_ticks = usec_count;
//time_us = end_ticks - start_ticks;
//#endif

//debug functionality

#ifdef VERBOSE

unsigned_byte src[] ={'0','1','2','3'};
char str[] = {"Hello World"};
UART_configure();
unsigned_byte send_var = (unsigned_byte)'S';
UART_send(&send_var);

LOG_RAW_DATA(src,4);
LOG_RAW_STRING(str);
LOG_RAW_INT(1523);
#endif


RTC_config();

LQ_buf_ptr = (LQ_t*)malloc(sizeof(LQ_t));
if(LQ_buf_ptr != NULL) {


LQ_init(LQ_buf_ptr,256);

while(1){

//write new heartbeat data to the buffer
//if(heartbeat_flag == 1){
//	LQ_buffer_add_item(LQ_buf_ptr,heartbeat_data);
//	heartbeat_flag = 0;
//
//}

//if logger buffer not empty  send out data
if(!(  LQ_is_empty(LQ_buf_ptr) == Buffer_Empty   ) )
{

LQ_buffer_remove_item(LQ_buf_ptr,&out_data);
LOG_RAW_INT( out_data.time_sec);

}

}
free(LQ_buf_ptr);
}

}


void clock_config(void){
//BOARD_BootClockRUN();
BOARD_InitDebugConsole();
//enable clock for dma
SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
//enable clock for dmaMux
SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
}




