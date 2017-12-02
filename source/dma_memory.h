
#include <stdint.h>
#include <stddef.h>

#ifndef FILE_MEMORY_DMA
#define FILE_MEMORY_DMA


/*******************************************************************************
@brief:Moves data from source memory location to destination using DMA

This function takes two byte pointers(src & dst) and a length of bytes to move
 from the source location to the destination.
@param:pointer to source memory, pointer to destination memory, length of data
in bytes
@return:pointer to destination memory.
*******************************************************************************/
uint8_t* memmove_dma(uint8_t* src, uint8_t* dst, size_t length);



/*******************************************************************************
@brief:Sets given value to the given memory locations

This function takes a pointer to a source memory location, length in bytes and
set all locations of that memory to the given value.
@param:pointer to source memory, length of memory in bytes, value to be set
@return:pointer to source memory.
*******************************************************************************/
uint8_t* memset_dma(uint8_t*, size_t , uint8_t);



#endif
