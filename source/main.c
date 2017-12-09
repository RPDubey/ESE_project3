/*******************************************************************************
@file:main.c
@brief:entry point for project

entry point for project@author:Ravi Dubey
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
