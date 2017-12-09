/*******************************************************************************
@file:RTC.c
@brief:function declarations for configuring RTC to implement a 'heartbeat'

This file provides definitions for RTC related functions declared in RTC.h
@author:Ravi Dubey
@date:12/2/2017
*******************************************************************************/

#include<MKL25Z4.h>

#include<stdlib.h>
#include"RTC.h"
#include"logger_que.h"
#include"common.h"
#include"project3.c"



extern LQ_t* LQ_buf_ptr;
extern LQ_t* HB_buf_ptr;
extern uint8_t verbose_flag;
log_data_struct heartbeat_data;
uint8_t heartbeat_flag;

void RTC_config(void){

	//static payload for HEARBEAT
	heartbeat_data.ID = HEARTBEAT;
	heartbeat_data.log_length = 0;
	heartbeat_data.payload_start_ptr = NULL;
	heartbeat_data.checksum = 0;

	NVIC_EnableIRQ(RTC_Seconds_IRQn );

	SIM->SOPT1 |= (1UL<<18) | (1UL<<19) ; //select 1KHZ osc LPO for rtc counter
	SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;//enable software access and interrupts to RTC

	// wait for clock to stabilize
	uint32_t j =48000;
	while(j){
		j--;
	}


	RTC_LR = 0x000000FF ;// unlock write access to registers
	RTC_CR =  0X00000004;//NOn supervisor mode acces enabled. rest zero

	RTC_TSR = 0x00000001;//Time seconds REgister.writing zero not recommended
    RTC_TAR = 0x00000000;//TAR never equals TSR, hence alarm flag always clear
	RTC_TPR = 0x00007FFF- 999 ;//14th bit goes low on 1000th count,triggerring interrupt

	RTC_IER = 0x00000010;//second interrupt enable
	RTC_SR  |=(1UL<<4); //status- enable counter

}

void RTC_Seconds_IRQHandler(void)
{
	RTC_SR  &= ~(1UL<<4); //disable counter
	RTC_TPR = 0x00007FFF-999 ;
	RTC_SR  |=(1UL<<4);   // enable counter
	sec_count++;
    heartbeat_data.time_sec = sec_count;

    //add data to a heartbeat buffer
#ifdef verbose
	if(verbose_flag == 1){
    LOG_RAW_INT(heartbeat_data.ID);
	LOG_RAW_INT(heartbeat_data.time_sec);
	LOG_RAW_INT(heartbeat_data.log_length);
	}
#endif
}
