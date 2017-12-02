#ifndef SOURCE_LOGGER_H_
#define SOURCE_LOGGER_H_

#include"circbuf.h"

/*************************************************************************
@brief:BLocked logging through UART

Takes a pointer to a sequence of bytes, length, and logs it out through UART
@param:none
@return:return_enum
*************************************************************************/
return_enum log_data(unsigned_byte*,size_t);

/*************************************************************************
@brief:Wrapper for log_data()

Takes a pointer to a sequence of bytes, length, and logs it out through UART
@param:none
@return:return_enum
*************************************************************************/
return_enum LOG_RAW_DATA(unsigned_byte*,size_t);


/*************************************************************************
@brief:BLocked logging through UART

Takes a C string, logs it out through UART to terminal
@param:none
@return:return_enum
*************************************************************************/
return_enum log_string(char**);

/*************************************************************************
@brief:wrapper for log_string()

Takes a C string, logs it out through UART to terminal
@param:none
@return:return_enum
*************************************************************************/
return_enum LOG_RAW_STRING(char**);



/*************************************************************************
@brief:BLocked logging through UART

Takes an integer and logs it out through UART using itoa()
@param:none
@return:return_enum
*************************************************************************/
return_enum log_integer(int);

/*************************************************************************
@brief:wrapper for log_integer()

Takes an integer and logs it out through UART using itoa()
@param:none
@return:return_enum
*************************************************************************/
return_enum LOG_RAW_INT(int);




/*************************************************************************
@brief:BLocked logging through UART

blocks until current buffer is empty
@param:none
@return:return_enum
*************************************************************************/
return_enum log_flush();

/*************************************************************************
@brief:Wrapper for log_flush()

blocks until current buffer is empty
@param:none
@return:return_enum
*************************************************************************/
return_enum LOG_FLUSH();






#endif /* SOURCE_LOGGER_H_ */
