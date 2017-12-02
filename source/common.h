/*
 * common.h
 *
 *  Created on: Dec 1, 2017
 *      Author: Ravi
 */

#ifndef SOURCE_COMMON_H_
#define SOURCE_COMMON_H_
#include<stdlib.h>
#define unsigned_byte uint8_t
//enum for return type of functions

typedef enum{
  Success ,
  Buffer_Full,
  Buffer_Empty,
  Null_Error,
  Argument_Error
}CB_enum;

typedef enum{
  Pass,
  Fail
}return_enum;


typedef enum{
	LOGGER_INITIALZED,
	GPIO_INITIALZED,
    SYSTEM_INITIALIZED,
	SYSTEM_HALTED,
	INFO,
	WARNING,
	ERROR,
	PROFILING_STARTED,
	PROFILING_RESULT,
	PROFILING_COMPLETED,
	DATA_RECEIVED,
	DATA_ANALYSIS_STARTED,
	DATA_ALPHA_COUNT,
	DATA_NUMERIC_COUNT,
	DATA_PUNCTUATION_COUNT,
	DATA_MISC_COUNT,
	DATA_ANALYSIS_COMPLETED
}LOG_ID;

typedef struct{
LOG_ID ID;
//Time stamp
size_t log_length;
//size_t payload;//payload
//checksum
}log_data_struct;

#define CB_data_type  log_data_struct



typedef struct{
  CB_data_type* buf_ptr;  //points to begining of buffer in memory
  CB_data_type* head;     // where to add item
  CB_data_type* tail;     //where to pop item
  size_t size;    //buffer size
  size_t count;   //current number of items on the buffer
  CB_data_type* buf_top_ptr; //points to the end of buffer in memory
}CB_t;

#endif /* SOURCE_COMMON_H_ */
