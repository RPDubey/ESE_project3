#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include"dma_memory.h"
#include"memory.h"

#include"systick.h"
#define len 10

int main(){
	uint8_t source[len];
	uint8_t dst[len];
	uint16_t i =0;
	for (i=0;i<len;i++){
		source[i] = 1;
		dst[i] = 0;
	}
//set up for profiling

volatile uint32_t start_ticks = 0;
volatile uint32_t end_ticks = 0;
volatile uint32_t time_us = 0;

Systick_config();

start_ticks = usec_count;
//memset(dst,len,1);
 my_memset(dst,len,1);
//memset_dma(dst,len,1);
//memmove_dma(source,dst,len);
end_ticks = usec_count;
time_us = end_ticks - start_ticks;
return 0;
}
