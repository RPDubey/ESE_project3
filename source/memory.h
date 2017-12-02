/********************************************************************************
@file:memory.h
@brief:An abstraction for memory operations implemented in memory.c

This file provides definitions for functions and external variables of file
memory.c
@author:Ravi Dubey
@date:09/23/2017
*******************************************************************************/


#ifndef FILE_MEMORY
#define FILE_MEMORY

#include <stdint.h>
#include <stddef.h>


/*******************************************************************************
@brief:Moves data from source memory location to destination

This function takes two byte pointers(src & dst) and a length of bytes to move
 from the source location to the destination.
@param:pointer to source memory, pointer to destination memory, length of data
in bytes
@return:pointer to destination memory.
*******************************************************************************/
uint8_t* my_memmove(uint8_t*, uint8_t*, size_t);


/*******************************************************************************
@brief:Copies data from source memory location to destination

This function takes two byte pointers(src & dst) and a length of bytes to copy
from the source location to the destination.
@param:pointer to source memory, pointer to destination memory, length of data
in bytes
@return:pointer to destination memory.
*******************************************************************************/
uint8_t* my_memcopy(uint8_t*, uint8_t*, size_t);

/*******************************************************************************
@brief:Sets given value to the given memory locations

This function takes a pointer to a source memory location, length in bytes and
set all locations of that memory to the given value.
@param:pointer to source memory, length of memory in bytes, value to be set
@return:pointer to source memory.
*******************************************************************************/
uint8_t* my_memset(uint8_t*, size_t , uint8_t);

/*******************************************************************************
@brief:Sets value zero to the given memory locations

This function takes a pointer to a source memory location, length in bytes and
set all locations of that memory to zero.
@param:pointer to source memory,length of memory in bytes
@return:pointer to source memory.
*******************************************************************************/
uint8_t* my_memzero(uint8_t*, size_t );


/*******************************************************************************
@brief:Reverse the order of bytes at given memory locations

This function takes a pointer to a source memory location, length in bytes and
reverses the order of all of the bytes.
@param:pointer to source memory,length of memory in bytes
@return:pointer to source memory.
*******************************************************************************/
uint8_t* my_reverse(uint8_t*, size_t );


/*******************************************************************************
@brief:reserve dynamic memory

This function takes number of words to allocate in dynamic memory
@param:length of memory in word(2 bytes)
@return:pointer to memory allocated.
*******************************************************************************/
int32_t* reserve_words(size_t );


/*******************************************************************************
@brief:deaalocate memory
This function deallocates dynamic memory by providing pointer source to the
function

@param:pointer to memory
@return:void
*******************************************************************************/
void free_words(int32_t* );

#endif
