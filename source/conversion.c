/********************************************************************************
@file:conversion.c
@brief:function declarations for conversion operation functions

This file declares functions for implementing conversion operations defined in
conversion.h
@author:Ravi Dubey
@date:09/23/2017
********************************************************************************/
# include <stdio.h>
# include <stdint.h>
# include "conversion.h"
//# include "platform.h"
# include "memory.h"


#define BYTE_3 (0xFF000000)
#define BYTE_2 (0x00FF0000)
#define BYTE_1 (0x0000FF00)
#define BYTE_0 (0x000000FF)

#define SHIFT_1BYTE (8)
#define SHIFT_2BYTE (16)
#define SHIFT_3BYTE (24)

uint8_t my_itoa(int32_t data, uint8_t* ptr, uint32_t base){

  if((base < 2) || (base >16) ){
    #ifdef ENABLE_LOWLEVEL_FUNCTION
    printf("Invalid Base. Aborting itoa\n" );
    #endif
    return -1;
  }

  if (ptr == NULL) {
    #ifdef ENABLE_LOWLEVEL_FUNCTION
    printf("Destination poiner is Null\n");
    #endif
    return -1;

  }
uint8_t string_length = 0;
uint8_t digit;
int8_t sign;

if(data == 0){
  *ptr = '0';
  *(ptr + 1) = '\0';
  return 2;
}

if(data > 0) sign = 1;
if(data < 0) sign = -1;

data = data*sign;//data made positive
*(ptr+string_length) = '\0';
string_length++;

while(data >0){

digit = data%base;
data = (data - digit)/base;//for next iteration

if(digit > 9) digit = (digit -10) + 'A'; // assign ascii value betwee A to F

else digit = digit + '0'; //assign ascii value of the digit
*(ptr + string_length) = digit;
string_length++;
}

if( (sign == -1) ){
  *(ptr + string_length) = '-';
  string_length++;
}
my_reverse(ptr,string_length);

return string_length;

}

int32_t my_atoi( uint8_t* ptr, uint8_t digits , uint32_t base){

  if((base < 2) || (base >16) ){
      #ifdef ENABLE_LOWLEVEL_FUNCTION
    printf("Invalid Base. Aborting atoi\n");
    #endif
    return -1;
  }

  if (ptr == NULL) {
      #ifdef ENABLE_LOWLEVEL_FUNCTION
    printf("Source poiner is Null.Aborting atoi\n" );
    #endif
    return -1;

  }
if (digits <= 0) {
    #ifdef ENABLE_LOWLEVEL_FUNCTION
  printf("Invalid digits. Aborting atoi\n");
  #endif
  return -1;
}

int8_t sign = 1;

if( *ptr == '-' ){
  sign = -1;
  ptr++;//point to the first digit rather than negative sign
  digits--;
}

my_reverse(ptr , digits);
ptr++;//skip the NULL
digits--;//null skipped

int32_t number_decimal = 0;
uint32_t power = 1;
uint8_t i ;

for(i = 0; i < digits; i++ ){

if( (*(ptr + i)  <= '9')  && (*(ptr + i) >= '0') ) { *(ptr+i)-= '0'; }
else if( (*(ptr + i)  <= 'F')  && (*(ptr + i) >= 'A' ) )  {*(ptr+i)-= 'A'; }
else {
  #ifdef ENABLE_LOWLEVEL_FUNCTION
  printf("Invalid ascii values. Aborting\n");
  #endif
  return -1;
}
number_decimal += *(ptr + i) * power ;
power = power * base ;
}
return number_decimal*sign ;
}

int8_t big_to_little32( uint32_t* data, uint32_t length){

if((data == NULL) || (length <= 0)){
  #ifdef ENABLE_LOWLEVEL_FUNCTION
  printf("Invalid Arguments\n");
  #endif
  return -1;
}
uint32_t i, temp1, temp2, temp3, temp4 = 0;

for(i = 0;i < length;i++){
temp1 = *(data + i) & BYTE_3>>SHIFT_3BYTE  ;
temp2 = *(data + i) & BYTE_2>>SHIFT_1BYTE  ;
temp3 = *(data + i) & BYTE_1<<SHIFT_1BYTE  ;
temp4 = *(data + i) & BYTE_0<<SHIFT_3BYTE  ;
*(data + i) = temp4 | temp3 | temp2 | temp1 ;
}
return 1;
}

int8_t little_to_big32( uint32_t* data, uint32_t length){

  if((data == NULL) || (length <= 0)){
    #ifdef ENABLE_LOWLEVEL_FUNCTION
    printf("Invalid Arguments\n");
    #endif
    return -1;
  }
  uint32_t i, temp1, temp2, temp3, temp4 = 0;

  for(i = 0;i < length;i++){
  temp1 = *(data + i) & BYTE_3>>SHIFT_3BYTE  ;
  temp2 = *(data + i) & BYTE_2>>SHIFT_1BYTE  ;
  temp3 = *(data + i) & BYTE_1<<SHIFT_1BYTE  ;
  temp4 = *(data + i) & BYTE_0<<SHIFT_3BYTE  ;
  *(data + i) = temp4 | temp3 | temp2 | temp1 ;
  }
  return 1;

}
