/*******************************************************************************
@file:systick.c
@brief:function declaration for systick configuration

This file declares systick config function
to another
@author:Ravi Dubey
@date:12/1/2017
*******************************************************************************/
#define project3

#include"project3.h"

#ifdef FRDM
#include"spi.h"
#include"gpio.h"
#include"nordic.h"
#endif

int main(void){

#ifdef project3
project_3() ;
#endif

while(1);
}
