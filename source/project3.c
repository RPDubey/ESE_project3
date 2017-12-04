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
#include"uart.h"

#define VERBOSE



LQ_t*__attribute__((section (".buffer"))) LQ_buf_ptr;//Logger Que Buffer ptr
LQ_t*__attribute__((section (".buffer"))) HB_buf_ptr;//HeartBeatData Buffer ptr

extern log_data_struct heartbeat_data;

log_data_struct* data_out;//this variable is used to pop data out and send over terminal

log_data_struct *data_flush;

void clock_config(void);
void project_3(void);

void project_3(void){

	BOARD_InitPins();
//	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();
	clock_config();

	UART_configure();
	log_data_struct HB_data_out ;

	log_data_struct data_log; //structure to store profiling data

	data_flush = (log_data_struct*)malloc(sizeof(log_data_struct) );
	data_out = (log_data_struct*)malloc(sizeof(log_data_struct) );
	LQ_buf_ptr = (LQ_t*)malloc(sizeof(LQ_t));
	HB_buf_ptr = (LQ_t*)malloc(sizeof(LQ_t));

	if( (LQ_buf_ptr == NULL) || (data_out == NULL)  || (HB_buf_ptr == NULL) || (data_flush == NULL) ) return ;

	LQ_init(LQ_buf_ptr,512);
	LQ_init(HB_buf_ptr,5*sizeof(log_data_struct));


	data_log.ID = LOGGER_INITIALZED ;
	data_log.time_sec = 0;
	data_log.log_length = 0;
	LOG_ITEM(&data_log,LQ_buf_ptr);

	RTC_config();
	while( (LQ_is_empty(HB_buf_ptr) == Buffer_Empty ) );//wait till first second count

	data_log.ID = SYSTEM_INITIALIZED;
	data_log.time_sec = sec_count;
	data_log.log_length = 0;
	LOG_ITEM(&data_log,LQ_buf_ptr);


	//start profiling section
#ifdef FRDM

	//start profiling
	data_log.ID = PROFILING_STARTED;
	data_log.time_sec = sec_count;
	data_log.log_length = 0;
	LOG_ITEM(&data_log,LQ_buf_ptr);

	//10 bytes
	//memmove profiling
	uint8_t source[5000];
	uint8_t dst[5000];
	uint16_t i =0;
	size_t len = 0;
	for (i=0;i<5000;i++){
		source[i] = 1;
		dst[i] = 0;
	}

	//set up for profiling
	volatile uint32_t start_ticks = 0;
	volatile uint32_t end_ticks = 0;
	volatile uint32_t time_us = 0;

	Systick_config();

	len = 5000;
	start_ticks = usec_count;
	memmove_dma(source,dst,len);
	end_ticks = usec_count;
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = sec_count;
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	len = 1000;
	start_ticks = usec_count;
	memmove_dma(source,dst,len);
	end_ticks = usec_count;
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = sec_count;
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	len = 100;
	start_ticks = usec_count;
	memmove_dma(source,dst,len);
	end_ticks = usec_count;
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = sec_count;
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	len = 10;
	start_ticks = usec_count;
	memmove_dma(source,dst,len);
	end_ticks = usec_count;
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = sec_count;
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	//memset profiling
	len = 5000;
	start_ticks = usec_count;
	memset_dma(dst,len,1);
	end_ticks = usec_count;
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = sec_count;
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	len = 1000;
	start_ticks = usec_count;
	memset_dma(dst,len,1);
	end_ticks = usec_count;
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = sec_count;
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	len = 100;
	start_ticks = usec_count;
	memset_dma(dst,len,1);
	end_ticks = usec_count;
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = sec_count;
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	len = 10;
	start_ticks = usec_count;
	memset_dma(dst,len,1);
	end_ticks = usec_count;
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = sec_count;
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);


	//profiling completed
	data_log.ID = PROFILING_COMPLETED;
	data_log.time_sec = sec_count;
	data_log.log_length = 0;
	LOG_ITEM(&data_log,LQ_buf_ptr);

	//disable systick used for profiling
	SysTick->CTRL &= ~(1UL)  ;

#endif


	while(1){
		if(!(  LQ_is_empty(HB_buf_ptr) == Buffer_Empty   ) )
		{

			LQ_buffer_remove_item(HB_buf_ptr,&HB_data_out);
#ifdef verbose
			if(verbose_flag == 1){
			LOG_RAW_INT(HB_data_out.ID);
			LOG_RAW_INT(HB_data_out.time_sec);
			LOG_RAW_INT(HB_data_out.log_length);
		}
#endif
		}
	}

	free(LQ_buf_ptr);
	free (data_out);
	free(HB_buf_ptr);
//	free(command_CB);

}


void clock_config(void){

	//BOARD_BootClockRUN();

	//enable clock for dma
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	//enable clock for dmaMux
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;


}




