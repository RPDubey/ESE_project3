/*******************************************************************************
@file:cirLQuf.c
@brief:function declarations for implementing circular buffer operations

This file provides definitions for LQ related functions declared declared in
cirLQuf.h
@author:Ravi Dubey
@date:10/21/2017
 *******************************************************************************/

#include<stdlib.h>
#include"common.h"
#include"logger_que.h"


CB_enum LQ_init(LQ_t* LQ_ptr, size_t LQ_size ){

	if(LQ_ptr == NULL || LQ_size == 0) return (CB_enum)Argument_Error;

	CB_enum return_val;
	LQ_ptr->buf_ptr =(log_data_struct*)malloc(LQ_size);
	return_val = (LQ_ptr->buf_ptr == NULL)? Null_Error:Success ;
	if(return_val != Success) return return_val;
	LQ_ptr->size = LQ_size;
	LQ_ptr->head = LQ_ptr->buf_ptr ;
	LQ_ptr->tail = LQ_ptr->buf_ptr ;
	LQ_ptr->count = 0;
	LQ_ptr->buf_top_ptr = (LQ_ptr->buf_ptr + LQ_size * sizeof(log_data_struct) - 1);
	return return_val;

}



CB_enum LQ_destroy(LQ_t* LQ_ptr){

	if(LQ_ptr == NULL ) return (CB_enum)Argument_Error;
	free(LQ_ptr->buf_ptr); // free LQ storage
	free(LQ_ptr);          // free LQ structure
	return (CB_enum)Success ;
}

