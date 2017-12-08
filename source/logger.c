/*******************************************************************************
@file:logger.c
@brief:function declarations for binary logger functions
This file declares functions for implementing operations defined in logger.h
@author:Ravi Dubey
@date:12/1/2017
 *******************************************************************************/

#include<stdint.h>
#include"logger.h"
#include"common.h"
#include"logger_que.h"
#include"uart.h"
#include"conversion.h"

//#define FRDM

extern log_data_struct* data_out ;
extern log_data_struct *data_flush;

return_enum log_data(unsigned_byte* src_ptr, size_t len){

	if(src_ptr == NULL) return (return_enum)Fail;

	return UART_send_n(src_ptr,len);

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


return_enum log_flush(LQ_t* LQ_buf_ptr){


	while( LQ_is_empty(LQ_buf_ptr) != Buffer_Empty ){
		LQ_buffer_remove_item(LQ_buf_ptr,data_flush);

		switch( (data_flush->ID)  ){

			case LOGGER_INITIALZED:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);

				break;

			case GPIO_INITIALZED:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);
				break;

			case SYSTEM_INITIALIZED:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);
				break;

			case SYSTEM_HALTED:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);
				break;

			case INFO:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);
				LOG_RAW_STRING((char*)data_flush->payload_start_ptr);
				LOG_RAW_INT(data_flush->checksum);
				break;

			case WARNING:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);
				LOG_RAW_STRING((char*)data_flush->payload_start_ptr);
				LOG_RAW_INT(data_flush->checksum);
				break;

			case ERROR:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);
				LOG_RAW_STRING((char*)data_flush->payload_start_ptr);
				LOG_RAW_INT(data_flush->checksum);
				break;

			case PROFILING_STARTED:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);
				break;

			case PROFILING_RESULT:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);
				LOG_RAW_INT(*((int*)data_flush->payload_start_ptr));
				LOG_RAW_INT(data_flush->checksum);

		        break;

			case PROFILING_COMPLETED:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);
				break;

			case DATA_RECEIVED:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);
				break;

			case DATA_ANALYSIS_STARTED:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);
				break;

			case DATA_ALPHA_COUNT:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);
				LOG_RAW_INT(*((int*)data_flush->payload_start_ptr));
				LOG_RAW_INT(data_flush->checksum);
				break;

			case DATA_NUMERIC_COUNT:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);
				LOG_RAW_INT(*((int*)data_flush->payload_start_ptr));
				LOG_RAW_INT(data_flush->checksum);
				break;

			case DATA_PUNCTUATION_COUNT:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);
				LOG_RAW_INT( *((int*)data_flush->payload_start_ptr));
				LOG_RAW_INT(data_flush->checksum);
				break;

			case DATA_MISC_COUNT:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);
				LOG_RAW_INT( *((int*)data_flush->payload_start_ptr));
				LOG_RAW_INT(data_flush->checksum);
				break;

			case DATA_ANALYSIS_COMPLETED:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);
				break;

			case HEARTBEAT:
				LOG_RAW_INT(data_flush->ID);
				LOG_RAW_INT(data_flush->time_sec);
				LOG_RAW_INT(data_flush->log_length);
				break;

		}}

return 0;
}




return_enum log_item(log_data_struct* data, LQ_t* Buffer){


#ifdef verbose
	uint8_t ret;

	//add data to buffer head
	ret = LQ_buffer_add_item(Buffer,*data);
	if(ret == (CB_enum)Argument_Error) return 1;

	//pop data from buffer tail

	ret = LQ_buffer_remove_item(Buffer,data_out);

	if(ret == (CB_enum)Argument_Error) return 1;

	calc_checksum(data_out);

	//write out to terminal based on type of data
	switch( (data_out->ID)  ){

	case LOGGER_INITIALZED:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);

		break;

	case GPIO_INITIALZED:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);
		break;

	case SYSTEM_INITIALIZED:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);
		break;

	case SYSTEM_HALTED:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);
		break;

	case INFO:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);
		LOG_RAW_STRING((char*)data_out->payload_start_ptr);
		LOG_RAW_INT(data_out->checksum);
		break;

	case WARNING:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);
		LOG_RAW_STRING((char*)data_out->payload_start_ptr);
		LOG_RAW_INT(data_out->checksum);
		break;

	case ERROR:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);
		LOG_RAW_STRING((char*)data_out->payload_start_ptr);
		LOG_RAW_INT(data_out->checksum);
		break;

	case PROFILING_STARTED:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);
		break;

	case PROFILING_RESULT:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);
		LOG_RAW_INT(*((int*)data_out->payload_start_ptr));
		LOG_RAW_INT(data_out->checksum);

        break;

	case PROFILING_COMPLETED:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);
		break;

	case DATA_RECEIVED:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);
		break;

	case DATA_ANALYSIS_STARTED:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);
		break;

	case DATA_ALPHA_COUNT:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);
		LOG_RAW_INT(*((int*)data_out->payload_start_ptr));
		LOG_RAW_INT(data_out->checksum);
		break;

	case DATA_NUMERIC_COUNT:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);
		LOG_RAW_INT(*((int*)data_out->payload_start_ptr));
		LOG_RAW_INT(data_out->checksum);
		break;

	case DATA_PUNCTUATION_COUNT:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);
		LOG_RAW_INT( *((int*)data_out->payload_start_ptr));
		LOG_RAW_INT(data_out->checksum);
		break;

	case DATA_MISC_COUNT:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);
		LOG_RAW_INT( *((int*)data_out->payload_start_ptr));
		LOG_RAW_INT(data_out->checksum);
		break;

	case DATA_ANALYSIS_COMPLETED:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);
		break;

	case HEARTBEAT:
		LOG_RAW_INT(data_out->ID);
		LOG_RAW_INT(data_out->time_sec);
		LOG_RAW_INT(data_out->log_length);
		break;



	}

#endif
return 0;
}

/****************Wrapper Functions*****************************/

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

return_enum LOG_FLUSH(LQ_t* Buffer){
#ifdef verbose
if(verbose_flag==1) {
#ifdef FRDM
	return log_flush(Buffer);
#endif

#ifdef BBB


#endif
}
#endif
return 1;
}


CB_enum LOG_ITEM(log_data_struct* data , LQ_t* Buffer){
#ifdef verbose
if(verbose_flag==1) {
#ifdef FRDM
	return log_item(data,Buffer);
#endif

#ifdef BBB
#endif
}
#endif
return 1;
}
