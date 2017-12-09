/*******************************************************************************
@file:project3.c
@brief:project3 functions

This file initializes all the functionality for project3
@author:Ravi Dubey
@date:12/1/2017
 *******************************************************************************/


#include"memory.h"
#include"circbuf.h"
#include"logger_que.h"
#include"common.h"
#include"project3.h"

#include<stdint.h>
#include<stdlib.h>



#ifdef FRDM
#include"pin_mux.c"
#include"clock_config.c"
#include "board.h"
#include"dma_memory.h"
#include"systick.h"
#include"uart.h"
#include "RTC.h"
#include"uart.h"
#include"nordic.h"
#include"spi.h"
#include"gpio.h"
#include"nordic.h"

#define newline()  LOG_RAW_STRING("\n\r");
#endif

#ifndef FRDM
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<signal.h>

#define newline()  LOG_RAW_STRING("\n");

#endif





#define get_time() sec_count
#define verbose


uint8_t verbose_flag ;
volatile uint32_t sec_count;
//extern volatile uint32_t usec_count ;


//LQ_t*__attribute__((section (".buffer"))) LQ_buf_ptr;//Logger Que Buffer ptr
//LQ_t*__attribute__((section (".buffer"))) HB_buf_ptr;//HeartBeatData Buffer ptr

LQ_t* LQ_buf_ptr;//Logger Que Buffer ptr
LQ_t* HB_buf_ptr;//HeartBeatData Buffer ptr



extern log_data_struct heartbeat_data;

log_data_struct* data_out;//this variable is used to pop data out and send over terminal

log_data_struct *data_flush;


void delay_us(size_t i){

	i = 48*i;
	while(i) i--;

}



void clock_configure(void){
#ifdef FRDM
	//BOARD_BootClockRUN();

	//enable clock for dma
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	//enable clock for dmaMux
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
#endif

}

log_data_struct heartbeat_data;
//char HB[]="HB";


#ifndef FRDM



void handle(int sig) {

	signal(SIGALRM, SIG_IGN);
	signal(SIGALRM,handle);
	alarm(1);
	sec_count++;
	heartbeat_data.time_sec = sec_count;



#ifdef verbose
	if(verbose_flag == 1){
		LOG_RAW_STRING("\n");//curiously, logging dosent happen without this
		LOG_RAW_INT(heartbeat_data.ID);
		LOG_RAW_INT(heartbeat_data.time_sec);
		LOG_RAW_INT(heartbeat_data.log_length);}

#endif


}
#endif



void HeartBeat_config(){

	//static payload for HEARBEAT
	heartbeat_data.ID = HEARTBEAT;
	heartbeat_data.log_length = 0;
	heartbeat_data.payload_start_ptr = NULL;
	heartbeat_data.checksum = 0;

#ifdef FRDM

	RTC_config();
	delay_us(1000);

#endif


#ifndef FRDM
	signal(SIGALRM, handle);
	alarm(1);

#endif

}



/*****************************************************************************/
void project_3(void){

	//LOG_RAW_STRING(welcome);

	verbose_flag = 1;
	sec_count = 0;
	//printf("Project3\n");


#ifdef FRDM
	BOARD_InitPins();
	//	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();
	clock_configure();
	UART_configure();
#endif




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

	HeartBeat_config();


	//printf("project3\n");

	data_log.ID = SYSTEM_INITIALIZED;
	data_log.time_sec = get_time();
	data_log.log_length = 0;
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();

	//start profiling
	data_log.ID = PROFILING_STARTED;
	data_log.time_sec = get_time();
	data_log.log_length = 0;
	LOG_ITEM(&data_log,LQ_buf_ptr);
	newline();

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


	//Profiling for FRDM
#ifdef FRDM

	//profiling variables

	//start DMA version profiling section

	Systick_config();

	newline();
	len = 5000;
	start_ticks = usec_count;
	memmove_dma(source,dst,len);
	end_ticks = usec_count;
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	len = 1000;
	start_ticks = usec_count;
	memmove_dma(source,dst,len);
	end_ticks = usec_count;
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	len = 100;
	start_ticks = usec_count;
	memmove_dma(source,dst,len);
	end_ticks = usec_count;
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	len = 10;
	start_ticks = usec_count;
	memmove_dma(source,dst,len);
	end_ticks = usec_count;
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	//memset profiling
	len = 5000;
	start_ticks = usec_count;
	memset_dma(dst,len,1);
	end_ticks = usec_count;
	time_us = end_ticks - start_ticks;


	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	len = 1000;
	start_ticks = usec_count;
	memset_dma(dst,len,1);
	end_ticks = usec_count;
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	len = 100;
	start_ticks = usec_count;
	memset_dma(dst,len,1);
	end_ticks = usec_count;
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	len = 10;
	start_ticks = usec_count;
	memset_dma(dst,len,1);
	end_ticks = usec_count;
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);
	newline();

#endif

#ifndef FRDM
	//disable systick used for profiling
	SysTick->CTRL &= ~(1UL)  ;

#endif

	//Non DMA based profiling for memmove - library version


	start_ticks = get_precision_time();
	memmove(source,dst,len);
	end_ticks = get_precision_time();
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();

	len = 1000;
	start_ticks = get_precision_time();
	memmove(source,dst,len);
	end_ticks = get_precision_time();
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	len = 100;
	start_ticks = get_precision_time();
	memmove(source,dst,len);
	end_ticks = get_precision_time();
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	len = 10;
	start_ticks = get_precision_time();
	memmove(source,dst,len);
	end_ticks = get_precision_time();
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	//memset profiling
	len = 5000;
	start_ticks = get_precision_time();
	memset(dst,len,1);
	end_ticks = get_precision_time();
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	len = 1000;
	start_ticks = get_precision_time();
	memset(dst,len,1);
	end_ticks = get_precision_time();
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);


	newline();
	len = 100;
	start_ticks = get_precision_time();
	memset(dst,len,1);
	end_ticks = get_precision_time();
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	len = 10;
	start_ticks = get_precision_time();
	memset(dst,len,1);
	end_ticks = get_precision_time();
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);
	newline();




	//Non DMA based profiling for memmove - my version


	len = 5000;
	start_ticks = get_precision_time();
	my_memmove(source,dst,len);
	end_ticks = get_precision_time();
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	len = 1000;
	start_ticks = get_precision_time();
	my_memmove(source,dst,len);
	end_ticks = get_precision_time();
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	len = 100;
	start_ticks = get_precision_time();
	my_memmove(source,dst,len);
	end_ticks = get_precision_time();
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	len = 10;
	start_ticks = get_precision_time();
	my_memmove(source,dst,len);
	end_ticks = get_precision_time();
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);
	newline();
	//memset profiling


	len = 5000;
	start_ticks = get_precision_time();
	my_memset(dst,len,1);
	end_ticks = get_precision_time();
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	len = 1000;
	start_ticks = get_precision_time();
	my_memset(dst,len,1);
	end_ticks = get_precision_time();
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	len = 100;
	start_ticks = get_precision_time();
	my_memset(dst,len,1);
	end_ticks = get_precision_time();
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);

	newline();
	len = 10;
	start_ticks = get_precision_time();
	my_memset(dst,len,1);
	end_ticks = get_precision_time();
	time_us = end_ticks - start_ticks;

	data_log.ID = PROFILING_RESULT ;
	data_log.time_sec = get_time();
	data_log.log_length = 4;
	data_log.payload_start_ptr = (uint8_t*)&time_us;
	calc_checksum(&data_log);
	LOG_ITEM(&data_log,LQ_buf_ptr);
	newline();

	//profiling completed
	data_log.ID = PROFILING_COMPLETED;
	data_log.time_sec = get_time();
	data_log.log_length = 0;
	LOG_ITEM(&data_log,LQ_buf_ptr);

	//disable systick used for profiling
	SysTick->CTRL &= ~(1UL)  ;




	//Code for Nordic Chip read and write operations

	/************Nordic Chip Operations*******************/
#ifdef FRDM
	GPIO_nrf_init();

	SPI_init();

	delay_us(100);

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
#endif



	while(1);

	free(LQ_buf_ptr);
	free (data_out);
	free(HB_buf_ptr);



}


