/*******************************************************************************
@file:common.h
@brief:structures/variables common to most source files

structures/variables common to most source files@author:Ravi Dubey
@date:12/1/2017
 *******************************************************************************/

#ifndef SOURCE_COMMON_H_
#define SOURCE_COMMON_H_
#include<stdlib.h>
#include<stdint.h>

#define verbose

//#define FRDM


//enum for return type of functions
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
	DATA_ANALYSIS_COMPLETED,
	HEARTBEAT //TImestamp, logged once every second
}LOG_ID;

typedef struct{
	uint32_t time_sec;//Time stamp in second elapsed
	size_t log_length;//length of payload
	uint8_t* payload_start_ptr;//pointer to payload
	uint8_t checksum;//checksum
	LOG_ID ID;//type of log

}log_data_struct;

#define unsigned_byte uint8_t

typedef enum{
	Success ,
	Buffer_Full,
	Buffer_Empty,
	Null_Error,
	Argument_Error
}CB_enum;

//structures for Circular Buffer
typedef struct{
	unsigned_byte* buf_ptr;  //points to begining of buffer in memory
	unsigned_byte* head;     // where to add item
	unsigned_byte* tail;     //where to pop item
	size_t size;    //buffer size
	size_t count;   //current number of items on the buffer
	unsigned_byte* buf_top_ptr; //points to the end of buffer in memory
}CB_t;


//structure for logger Que
typedef struct{
	log_data_struct* buf_ptr;  //points to begining of buffer in memory
	log_data_struct* head;     // where to add item
	log_data_struct* tail;     //where to pop item
	size_t size;    //buffer size
	size_t count;   //current number of items on the buffer
	log_data_struct* buf_top_ptr; //points to the end of buffer in memory
}LQ_t;






#endif /* SOURCE_COMMON_H_ */
