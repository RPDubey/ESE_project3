/*
 * RTC.h
 *
 *  Created on: Dec 2, 2017
 *      Author: Ravi
 */

#ifndef SOURCE_RTC_H_
#define SOURCE_RTC_H_


volatile uint32_t RTC_sec_count;

/*************************************************************************
@brief:RTC configuration

Configures the RTC
@param:none
@return:none
*************************************************************************/
void RTC_config(void);


#endif /* SOURCE_RTC_H_ */
