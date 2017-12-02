
#include <stdint.h>
#include <stddef.h>

#ifndef FILE_MEMORY_DMA
#define FILE_MEMORY_DMA

uint8_t* memmove_dma(uint8_t* src, uint8_t* dst, size_t length);

#endif
