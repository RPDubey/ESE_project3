/*******************************************************************************
@file:logger_q.h
@brief:An abstraction for Logger buffer operations implemented in cirLQuf.c

This file provides definitions for functions and external variables of file
cirLQuf.c
@author:Ravi Dubey
@date:10/21/2017
*******************************************************************************/


#ifndef SOURCE_LOGGER_QUE_H_
#define SOURCE_LOGGER_QUE_H_

#ifdef FRDM
#include"core_cm0plus.h"
#endif

#include<stdlib.h>
#include"common.h"

#ifndef FRDM
#define __STATIC_INLINE static inline
#endif

#ifdef FRDM
#define START_CRITICAL() __disable_irq()
#define END_CRITICAL()  __enable_irq()
#endif

#ifndef FRDM
#define START_CRITICAL()
#define END_CRITICAL()
#endif



/*******************************************************************************
@brief:Implements adding items to Logger buffer
This function takes data to be added to the Logger buffer and the poiner to
the circulr buffer and adds the data to this LQ.
@param:Pointer to LQ, pointer to data to be added to this LQ
@return:CB_enum enumaration that specifies success failure etc.
*******************************************************************************/
__attribute__((always_inline)) __STATIC_INLINE CB_enum LQ_buffer_add_item( LQ_t* , log_data_struct );
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


/*******************************************************************************
@brief:Implements removing items from Logger buffer
This function gives pointer to the Logger buffer from which the data has to be
removed and the variable in which the removed data has to be stored.
@param:Pointer to LQ, pointer to the variable where popped data has to be saved
@return:CB_enum enumaration that specifies success failure etc.
*******************************************************************************/
__attribute__((always_inline)) __STATIC_INLINE CB_enum LQ_buffer_remove_item(LQ_t* , log_data_struct*);

//function definition for static function
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
	else (LQ_ptr->tail) ++;

	*( (log_data_struct*)data ) = *( (log_data_struct*)LQ_ptr->tail );

	LQ_ptr->count-- ;
	}
	END_CRITICAL();


	/*************sending data out to terminal************************/

	return (CB_enum)Success ;
  }
  else return (CB_enum)Buffer_Empty ;

}


/*******************************************************************************
@brief:Implements checking whether Logger buffer is full
This function takes poiner tothe circulr buffer and checks for full state.
@param:Pointer to LQ
@return:CB_enum enumaration that specifies success failure etc.
*******************************************************************************/
__attribute__((always_inline)) __STATIC_INLINE CB_enum LQ_is_full(LQ_t*);

//function definition as its inline
CB_enum LQ_is_full(LQ_t* LQ_ptr){
  if(LQ_ptr == NULL ) return (CB_enum)Argument_Error;
  if(LQ_ptr->count >= LQ_ptr->size ) return (CB_enum)Buffer_Full;
  return 0;
}

/*******************************************************************************
@brief:Implements checking whether Logger buffer is Empty
This function takes poiner tothe circulr buffer and checks for Empty state.
@param:Pointer to LQ
@return:CB_enum enumaration that specifies success failure etc.
*******************************************************************************/
__attribute__((always_inline)) __STATIC_INLINE CB_enum LQ_is_empty(LQ_t*);
//function definition as its inline
CB_enum LQ_is_empty(LQ_t* LQ_ptr){
  if(LQ_ptr == NULL ) return (CB_enum)Argument_Error;
  if(LQ_ptr->count == 0 ) return (CB_enum)Buffer_Empty;
  return 0;
};

///*******************************************************************************
//@brief:Implements seeking data in Logger buffer at particular location
//This function takes pointer to a Logger buffer, and position from head to peek
//into and  pointer where this data will be stored.
//@param:Pointer to LQ,position from head to seek into, pointer to adress where
//the data has to be stored.
//@return:CB_enum enumaration that specifies success failure etc.
//*******************************************************************************/
//CB_enum LQ_peek(LQ_t* ,size_t, log_data_struct* );
//


/*******************************************************************************
@brief:Implements initiatin a Logger buffer
This function poiner to the circulr buffer and size to be reserved for the LQ
in Bytes.
@param:Pointer to LQ, size of buffer in bytes.
@return:CB_enum enumaration that specifies success failure etc.
*******************************************************************************/
CB_enum LQ_init(LQ_t* LQ_ptr , size_t LQ_size);



/*******************************************************************************
@brief:Implements destroying the Logger buffer
This function takes pointer to the Logger buffer to be destroyed
@param:Pointer to LQ
@return:CB_enum enumaration that specifies success failure etc.
*******************************************************************************/
CB_enum LQ_destroy(LQ_t* LQ_ptr);



#endif /* SOURCE_LOGGER_QUE_H_ */
