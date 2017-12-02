/*
 * logger_que.h
 *
 *  Created on: Dec 2, 2017
 *      Author: Ravi
 */

#ifndef SOURCE_LOGGER_QUE_H_
#define SOURCE_LOGGER_QUE_H_

#include"stdlib.h"
#include "logger.h"
#include"common.h"
/*************************************************************************
@brief:Wrapper for log_data()

Takes a pointer to a sequence of bytes, length, and logs it out through UART
@param:pointer to dat, num of data
@return:return_enum
*************************************************************************/
return_enum LOG_RAW_DATA(unsigned_byte*,size_t);

/*************************************************************************
@brief:wrapper for log_string()

Takes a C string, logs it out through UART to terminal
@param:pointer to string array
@return:return_enum
*************************************************************************/
return_enum LOG_RAW_STRING(char*);

/*************************************************************************
@brief:wrapper for log_integer()

Takes an integer and logs it out through UART using itoa()
@param:integer
@return:return_enum
*************************************************************************/
return_enum LOG_RAW_INT(int);

/*************************************************************************
@brief:Wrapper for log_flush()

blocks until current buffer is empty
@param:none
@return:return_enum
*************************************************************************/
return_enum LOG_FLUSH();



/*************************************************************************
@brief:Wrapper for log_item

stores logging data in circular buffer
@param:pointer to data to be logged, C buffer to be logged into
@return:return_enum
*************************************************************************/
CB_enum LOG_ITEM(log_data_struct* , CB_t*);


#endif /* SOURCE_LOGGER_QUE_H_ */
