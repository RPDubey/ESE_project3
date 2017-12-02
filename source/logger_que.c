/********************************************************************************
@file:logger_que.c.c
@brief:function declarations for wrapper functions functions

This file declares functions for implementing wrappers defined in
file_que.h
@author:Ravi Dubey
@date:12/2/2017
********************************************************************************/

#include<stdlib.h>
#include"logger.h"
#include"logger_que.h"


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

return 1;

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

return 1;
}

return_enum LOG_RAW_INT(int digit){

#ifdef BBB
printf("%d",digit);
return 0;
#endif

#ifdef FRDM
return log_integer(digit);
#endif

return 1;
}

CB_enum LOG_ITEM(log_data_struct* data , CB_t* Buffer){
	return log_item(data,Buffer);
}


