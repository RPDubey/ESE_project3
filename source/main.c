#include<stdint.h>
#include<stdio.h>
#include<string.h>

#include"pin_mux.c"
#include"clock_config.c"

#include"dma_memory.h"
#include"memory.h"
#include"systick.h"
#include"circbuf.h"
#include"uart.h"
#include"logger.h"

#define VERBOSE
#define len 10

int main(){

BOARD_InitPins();
BOARD_BootClockRUN();



//#ifdef profiling
//	uint8_t source[len];
//	uint8_t dst[len];
//	uint16_t i =0;
//	for (i=0;i<len;i++){
//		source[i] = 1;
//		dst[i] = 0;
//	}
////set up for profiling
//
//volatile uint32_t start_ticks = 0;
//volatile uint32_t end_ticks = 0;
//volatile uint32_t time_us = 0;
//
//Systick_config();
//
//start_ticks = usec_count;
////memset(dst,len,1);
// my_memset(dst,len,1);
////memset_dma(dst,len,1);
////memmove_dma(source,dst,len);
//end_ticks = usec_count;
//time_us = end_ticks - start_ticks;
//#endif

//debug functionality
#ifdef VERBOSE

unsigned_byte src[] ={'0','1','2','3'};
char str[] = {"Hello World"};
UART_configure();
unsigned_byte send_var = (unsigned_byte)'S';
UART_send(&send_var);

LOG_RAW_DATA(src,4);
LOG_RAW_STRING(str);
LOG_RAW_INT(1523);
while(1);

#endif
return 0;
}
