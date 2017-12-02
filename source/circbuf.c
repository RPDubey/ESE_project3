
/*******************************************************************************
@file:circbuf.c
@brief:function declarations for implementing circular buffer operations

This file provides definitions for CB related functions declared declared in
circbuf.h
@author:Ravi Dubey
@date:10/21/2017
*******************************************************************************/

# include <stdlib.h>
# include "circbuf.h"
# include <stdio.h>
CB_enum CB_init(CB_t* CB_ptr, size_t CB_size ){

  if(CB_ptr == NULL || CB_size == 0) return (CB_enum)Argument_Error;

  CB_enum return_val;
  CB_ptr->buf_ptr =(unsigned_byte*)malloc(CB_size);
  return_val = (CB_ptr->buf_ptr == NULL)? Null_Error:Success ;
  if(return_val != Success) return return_val;
  CB_ptr->size = CB_size;
  CB_ptr->head = CB_ptr->buf_ptr ;
  CB_ptr->tail = CB_ptr->buf_ptr ;
  CB_ptr->count = 0;
  CB_ptr->buf_top_ptr = (CB_ptr->buf_ptr + CB_size * sizeof(unsigned_byte) - 1);
  return return_val;

}



CB_enum CB_destroy(CB_t* CB_ptr){

  if(CB_ptr == NULL ) return (CB_enum)Argument_Error;
  free(CB_ptr->buf_ptr); // free CB storage
  free(CB_ptr);          // free CB structure
  return (CB_enum)Success ;
}


CB_enum CB_buffer_add_item( CB_t* CB_ptr , unsigned_byte data ){

  if(CB_ptr == NULL ) return (CB_enum)Argument_Error;
 //if que not full, then move head to position where data has to be stored
 //and write it there


  if(CB_ptr->count < CB_ptr->size ){

    if(CB_ptr->head ==   CB_ptr->buf_top_ptr ){
      CB_ptr->head = CB_ptr->buf_ptr;

    }
    else CB_ptr->head ++ ;

    *(CB_ptr->head) = data;
    CB_ptr->count++;

    return (CB_enum)Success ;
  }
  else return (CB_enum)Buffer_Full ;
}



CB_enum CB_buffer_remove_item(CB_t* CB_ptr , unsigned_byte* data ){
  if(CB_ptr == NULL || data == NULL) return (CB_enum)Argument_Error;
 //If the buffer is not empty,then move tail to the next location and
 //read the data out at the new location.
  if(CB_ptr->count > 0 ){
    if(CB_ptr->tail ==   CB_ptr->buf_top_ptr ){
      CB_ptr->tail = CB_ptr->buf_ptr;
    }
    else CB_ptr->tail ++;
  *data = *CB_ptr->tail;
  CB_ptr->count-- ;

  return (CB_enum)Success ;
  }
  else return (CB_enum)Buffer_Empty ;

}


CB_enum CB_is_full(CB_t* CB_ptr){
  if(CB_ptr == NULL ) return (CB_enum)Argument_Error;
  if(CB_ptr->count >= CB_ptr->size ) return (CB_enum)Buffer_Full;

}


CB_enum CB_is_empty(CB_t* CB_ptr){
  if(CB_ptr == NULL ) return (CB_enum)Argument_Error;
  if(CB_ptr->count == 0 ) return (CB_enum)Buffer_Empty;
};


CB_enum CB_peek(CB_t* CB_ptr ,size_t loc, unsigned_byte* data ){
  if(CB_ptr == NULL || data == NULL) return (CB_enum)Argument_Error;
  unsigned_byte* temp_head = CB_ptr->head;
  while(loc != 0){
    if( temp_head ==  CB_ptr->buf_top_ptr ){
      temp_head = CB_ptr->buf_ptr;
    }
    else temp_head ++ ;
   loc--;
  }
*data = *temp_head;
return (CB_enum)Success;
}

void print_CB_enum(CB_enum return_val){

  switch (return_val) {
    case 0: printf("Success\n" );break;
    case 1: printf("Buffer_Full\n" );break;
    case 2: printf("Buffer_Empty\n" );break;
    case 3: printf("Null_Error\n" );break;
    case 4: printf("Argument_Error\n" );break;
  }
}
