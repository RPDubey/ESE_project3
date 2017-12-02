#include"dma_memory.h"
#include<stdint.h>
#include<MKL25Z4.h>
#include <stdint.h>
#include <stdlib.h>

extern uint32_t __BUFFER_START, __BUFFER_END;//symbols defined in the linker script
uint8_t* __attribute__((section (".buffer"))) temp_ptr;


static uint8_t flag =0;

uint8_t* memmove_dma(uint8_t* src, uint8_t* dst, size_t length){

//Null source or destination pointer
if (src == NULL) {
#ifdef ENABLE_LOWLEVEL_FUNCTION
printf("Invalid Source Address, memmove aborted\n");
#endif

return dst;
}

if (dst == NULL) {
#ifdef ENABLE_LOWLEVEL_FUNCTION
printf("Invalid destination Address, memmove aborted\n");
#endif


return dst;
}

//Length =0
if(length <= 0) {
#ifdef ENABLE_LOWLEVEL_FUNCTION
printf("Invalid length\n"); return dst;
#endif


}

 if (src == dst) {
   #ifdef ENABLE_LOWLEVEL_FUNCTION
printf("Source and Destination are same\n" );
   #endif


   return dst;
 }


 //uint8_t *temp_ptr = (uint8_t*)&__BUFFER_START;

 temp_ptr = (uint8_t*)malloc(length );

// if (temp_ptr      == NULL) {
//   #ifdef ENABLE_LOWLEVEL_FUNCTION
//printf("Malloc Failed\n");
//   #endif
//
// return NULL;}

 //enable clock for dma
 	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
 //enable clock for dmaMux
 	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

 /*
 Normal mode - DMAMUX is transparent
 source is "always on" line for sw activated mem to mem transfer
 1. Write 0x00 to DMA MUX Channel config.
 2. Configure channel 0 in the DMA, including enabling the channel.
 	 source adress reg
 	 dest address reg
 	 control reg
 	 status reg
 3. Write appropriate value to DMA MUX channel config
 4.start transfer by DCRn[START] .
 */

 //enable NVIC interrupt for channel 0 DMA
 NVIC_EnableIRQ(DMA0_IRQn);

 DMAMUX0_CHCFG0 = 0x00;

 //Transfer dosent happen without this clearing
DMA_DCR0 &= ~(DMA_DCR_START_MASK | DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK);//Clear Source size and Destination size fields.

DMAMUX0_CHCFG0 = 0xBC; // trigger disabled ,channel 60


 DMA_SAR0 = (uint32_t)src;
 DMA_DAR0 =(uint32_t)temp_ptr;
 DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length);//no. of bytes to be transferred


#define four_byte

#ifdef one_byte
 //1 byte transfer at a time with interrupt on completion
 DMA_DCR0 &= !((1UL<<30)| (1UL<<29) | (1UL<<28)|(1UL<<24)|(1UL<<23)|(1UL<<21)| (1UL<<18) | (0xFFUL<<8) | (0x3UL<<4) | 0xFUL );
 DMA_DCR0 |= (1UL<<31) | (1UL<<22) | (1UL<<20) | (1UL<<19) |(1UL<<17)   ;
 DMA_DCR0 |= (1UL<<16);

#endif

#ifdef two_byte
 //2 byte transfer at a time with interrupt on completion
 DMA_DCR0 &= !((1UL<<30)| (1UL<<29) | (1UL<<28)|(1UL<<24)|(1UL<<23)|(1UL<<20)| (1UL<<18)  | (0xFFUL<<8) | (0x3UL<<4) | 0xFUL );
 DMA_DCR0 |= (1UL<<31) | (1UL<<22) | (1UL<<21) | (1UL<<19) |(1UL<<17)  ;
 DMA_DCR0 |= (1UL<<16);

 #endif

#ifdef four_byte
 //4 byte transfer at a time with interrupt on completion
 DMA_DCR0 &= !((1UL<<30)| (1UL<<29) | (1UL<<28)|(1UL<<24)|(1UL<<23)|(1UL<<21)| (1UL<<20) |(1UL<<18) | (0xFFUL<<8) | (0x3UL<<4) | 0xFUL );
 DMA_DCR0 |= (1UL<<31) | (1UL<<22) | (1UL<<19) |(1UL<<17)  ;
 DMA_DCR0 |= (1UL<<16);
 #endif

while(!flag);
flag= 0;

//Transfer dosent happen without this clearing
DMA_DCR0 &= ~(DMA_DCR_START_MASK | DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK);//Clear Source size and Destination size fields.

DMAMUX0_CHCFG0 = 0x00;
DMAMUX0_CHCFG0 = 0xBC; // trigger disabled ,channel 60

DMA_SAR0 = (uint32_t)temp_ptr;
DMA_DAR0 =(uint32_t)dst;
DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length);//no. of bytes to be transferred

#ifdef one_byte
//1 byte transfer at a time with interrupt on completion
DMA_DCR0 &= !((1UL<<30)| (1UL<<29) | (1UL<<28)|(1UL<<24)|(1UL<<23)|(1UL<<21)| (1UL<<18) | (0xFFUL<<8) | (0x3UL<<4) | 0xFUL );
DMA_DCR0 |= (1UL<<31) | (1UL<<22) | (1UL<<20) | (1UL<<19) |(1UL<<17)   ;
DMA_DCR0 |= (1UL<<16);

#endif

#ifdef two_byte
//2 byte transfer at a time with interrupt on completion
DMA_DCR0 &= !((1UL<<30)| (1UL<<29) | (1UL<<28)|(1UL<<24)|(1UL<<23)|(1UL<<20)| (1UL<<18)  | (0xFFUL<<8) | (0x3UL<<4) | 0xFUL );
DMA_DCR0 |= (1UL<<31) | (1UL<<22) | (1UL<<21) | (1UL<<19) |(1UL<<17)  ;
DMA_DCR0 |= (1UL<<16);

#endif

#ifdef four_byte
//4 byte transfer at a time with interrupt on completion
DMA_DCR0 &= !((1UL<<30)| (1UL<<29) | (1UL<<28)|(1UL<<24)|(1UL<<23)|(1UL<<21)| (1UL<<20) |(1UL<<18) | (0xFFUL<<8) | (0x3UL<<4) | 0xFUL );
DMA_DCR0 |= (1UL<<31) | (1UL<<22) | (1UL<<19) |(1UL<<17)  ;
DMA_DCR0 |= (1UL<<16);
#endif

while(!flag);

free(temp_ptr);

return dst;

}

void DMA0_IRQHandler(void){
//clear DONE before reprogramming the DMA.
DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
flag = 1;
}
