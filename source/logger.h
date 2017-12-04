#ifndef SOURCE_LOGGER_H_
#define SOURCE_LOGGER_H_

#include"circbuf.h"
#include"common.h"
#include<stdlib.h>
#include"core_cm0plus.h"

/*************************************************************************
@brief:Calculates checksum

Takes a pointer to a logger data structure and calculates and sets the
checksum field of the structure
@param:pointer to dat, num of data
@return:return_enum
*************************************************************************/
__attribute__((always_inline)) __STATIC_INLINE return_enum calc_checksum(log_data_struct*);

return_enum calc_checksum(log_data_struct* data_ptr){


	if(data_ptr->log_length < 1) return 0;

	uint8_t temp = 0x00;

	for(size_t i =0;i < (data_ptr->log_length);i++){

	temp ^= *(data_ptr->payload_start_ptr + i);

	}
	data_ptr->checksum = temp;
	return 0;
}

/*************************************************************************
@brief:BLocked logging through UART

Takes a pointer to a sequence of bytes, length, and logs it out through UART
@param:pointer to dat, num of data
@return:return_enum
*************************************************************************/
return_enum log_data(unsigned_byte*,size_t);



/*************************************************************************
@brief:BLocked logging through UART

Takes a C string, logs it out through UART to terminal
@param:pointer to string array
@return:return_enum
*************************************************************************/
return_enum log_string(char*);



/*************************************************************************
@brief:BLocked logging through UART

Takes an integer and logs it out through UART using itoa()
@param:integer
@return:return_enum
*************************************************************************/
return_enum log_integer(int);



/*************************************************************************
@brief:BLocked logging through UART

blocks until current buffer is empty
@param:none
@return:return_enum
*************************************************************************/
return_enum log_flush(LQ_t*);


/*************************************************************************
@brief:Non BLocked logging through Buffer

stores logging data in circular buffer
@param:pointer to data to be logged, C buffer to be logged into
@return:return_enum
*************************************************************************/
return_enum log_item(log_data_struct* , LQ_t*);


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
return_enum LOG_FLUSH(LQ_t*);



/*************************************************************************
@brief:Wrapper for log_item

stores logging data in circular buffer
@param:pointer to data to be logged, C buffer to be logged into
@return:return_enum
*************************************************************************/
CB_enum LOG_ITEM(log_data_struct* , LQ_t*);


#endif /* SOURCE_LOGGER_H_ */
