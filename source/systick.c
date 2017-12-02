#include<stdint.h>
#include"systick.h"
#include<MKL25Z4.h>

void Systick_config(){
usec_count = 0;
#define SysTick_Enable_Mask      (1UL)  //enable systick
#define SysTick_Exception_Mask   (1UL << 1) //raise exception on overflow
#define Processor_ClkSrc         (1UL << 2) //48 MHz processor clock


SysTick->LOAD = 47;  // reload value is 47 for overflow after 48 counts for 1 us ticks
SysTick->VAL = 0x00;  //clear current value
SysTick->CTRL |= SysTick_Enable_Mask | SysTick_Exception_Mask | Processor_ClkSrc ;

}


void SysTick_Handler(){
usec_count++;
}
