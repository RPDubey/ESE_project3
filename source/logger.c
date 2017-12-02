/*******************************************************************************
@file:logger.c
@brief:function declarations for binary logger functions
This file declares functions for implementing operations defined in logger.h
@author:Ravi Dubey
@date:12/1/2017
*******************************************************************************/

#include<stdint.h>
#include"logger.h"
#include"uart.h"
#include"conversion.h"

#define FRDM


return_enum log_data(unsigned_byte* src_ptr, size_t len){

	if(src_ptr == NULL) return (return_enum)Fail;

	return UART_send_n(src_ptr,len);

}

return_enum LOG_RAW_DATA(unsigned_byte* src_ptr,size_t len){

if(src_ptr == NULL) return 1;

#ifdef BBB
size_t i;
for(i=0;i<len;i++){
printf("%u ",*(src_ptr+i));
}
return 0;
#endif

#ifdef FRDM
return log_data(src_ptr,len);
#endif


}


return_enum log_string(char* string_ptr){

	uint8_t ret_val;

	if(string_ptr == NULL) return (return_enum)Fail;


	while(*string_ptr != '\0'){

		ret_val = UART_send((unsigned_byte*)string_ptr);

		if(ret_val != (return_enum)Pass) break;
		string_ptr++;
		}
	return ret_val;
}

return_enum LOG_RAW_STRING(char* string_ptr){
if(string_ptr == NULL) return 1;

#ifdef BBB
printf("%s",string_ptr);
return 0;
#endif

#ifdef FRDM
log_string(string_ptr);
return 0;
#endif

}


return_enum log_integer(int digit){

	uint8_t ret_val,ret;
	uint8_t* temp_char = (uint8_t*)malloc(10);

	if(temp_char == NULL) return (return_enum)Fail;

	ret_val = my_itoa(digit,temp_char, (uint32_t)10);
	if(ret_val == -1) return (return_enum)Fail;

	ret = UART_send_n((uint8_t*)temp_char,ret_val) ;

    free(temp_char);
	return ret;
}

return_enum LOG_RAW_INT(int digit){

#ifdef BBB
printf("%d",digit);
return 0;
#endif

#ifdef FRDM
return log_integer(digit);
#endif

}

