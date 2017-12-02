#include<stdint.h>
#include"dma_memory.h"
#include"systick.h"
#define len 5000

int main(){
	uint8_t source[len];
	uint8_t dst[len];
	uint16_t i =0;
	for (i=0;i<len;i++){
		source[i] = 1;
		dst[i] = 0;
	}

memmove_dma(source,dst,len);

return 0;
}
