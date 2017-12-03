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


CB_enum LQ_buffer_add_item( LQ_t* LQ_ptr , log_data_struct data ){

  if(LQ_ptr == NULL ) return (CB_enum)Argument_Error;
 //if que not full, then move head to position where data has to be stored
 //and write it there


  if(LQ_ptr->count < LQ_ptr->size ){

	START_CRITICAL();
	if(LQ_ptr->head ==   LQ_ptr->buf_top_ptr ){
	  LQ_ptr->head = LQ_ptr->buf_ptr;

	}
	else LQ_ptr->head ++ ;

	*(LQ_ptr->head) = data;
	LQ_ptr->count++;

	END_CRITICAL();
	return (CB_enum)Success ;
  }
  else return (CB_enum)Buffer_Full ;
}



CB_enum LQ_buffer_remove_item(LQ_t* LQ_ptr , log_data_struct* data ){
  if(LQ_ptr == NULL || data == NULL) return (CB_enum)Argument_Error;
 //If the buffer is not empty,then move tail to the next location and
 //read the data out at the new location.
  if(LQ_ptr->count > 0 ){
	START_CRITICAL();
	{
	if(LQ_ptr->tail ==   LQ_ptr->buf_top_ptr ){
	LQ_ptr->tail = LQ_ptr->buf_ptr;
	}
	else LQ_ptr->tail ++;
	*data = *LQ_ptr->tail;
	LQ_ptr->count-- ;
	}
	END_CRITICAL();

  return (CB_enum)Success ;
  }
  else return (CB_enum)Buffer_Empty ;

}


CB_enum LQ_peek(LQ_t* LQ_ptr ,size_t loc, log_data_struct* data ){
  if(LQ_ptr == NULL || data == NULL) return (CB_enum)Argument_Error;
  log_data_struct* temp_head = LQ_ptr->head;
  while(loc != 0){
    if( temp_head ==  LQ_ptr->buf_top_ptr ){
      temp_head = LQ_ptr->buf_ptr;
    }
    else temp_head ++ ;
   loc--;
  }
*data = *temp_head;
return (CB_enum)Success;
}

//void print_CB_enum(CB_enum return_val){
//
//  switch (return_val) {
//    case 0: printf("Success\n" );break;
//    case 1: printf("Buffer_Full\n" );break;
//    case 2: printf("Buffer_Empty\n" );break;
//    case 3: printf("Null_Error\n" );break;
//    case 4: printf("Argument_Error\n" );break;
//  }
//}


