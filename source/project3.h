#ifndef project3_HEAD
#define project3_HEAD

#ifndef FRDM
#include<time.h>
struct timespec start_time;
struct timespec current_time;
#endif

#include<stdint.h>
__attribute__((always_inline)) static inline uint32_t get_precision_time(void);

uint32_t get_precision_time(void){
#ifdef FRDM
return usec_count;
#endif

#ifndef FRDM
clock_gettime(CLOCK_MONOTONIC,&start_time);
return (start_time.tv_sec *1000000 + start_time.tv_sec) ;
#endif
return 1;
}


void HeartBeat_config(void);
void clock_configure(void);
void project_3(void);
#endif
