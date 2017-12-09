#ifndef project3_HEAD
#define project3_HEAD


#ifndef FRDM
#include<time.h>
#include"common.h"
struct timespec start_time;
struct timespec current_time;
#endif

#include<stdint.h>

volatile uint32_t usec_count ;

/********************************************************************************
@brief:Reads get time in usec

get time in usec
@param:none
@return:uint32_t
 ********************************************************************************/

__attribute__((always_inline)) static inline uint32_t get_precision_time(void);

uint32_t get_precision_time(void){
#ifdef FRDM
	return usec_count;
#endif

#ifndef FRDM
	clock_gettime(CLOCK_MONOTONIC,&start_time);
	return (start_time.tv_sec *1000000 + start_time.tv_sec) ;
#endif
	return 1;
}

/********************************************************************************
@brief:spinning delay in usec

spinning delay in usec
@param:none
@return:none
 ********************************************************************************/
void delay_us(size_t );

/********************************************************************************
@brief:Configure Heartbeat

configure RTC, Signal Handler based on Platform
@param:none
@return:none
 ********************************************************************************/
void HeartBeat_config(void);

/********************************************************************************
@brief:Configure clock
@param:none
@return:none
 ********************************************************************************/
void clock_configure(void);


/********************************************************************************
@brief:All operations related to project3
@param:none
@return:none
 ********************************************************************************/
void project_3(void);
#endif
