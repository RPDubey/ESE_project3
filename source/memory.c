/*******************************************************************************
@file:memory.c
@brief:function declaration for memory copy operation

This file declares function my_memmove for copying data from one memory location
to another
@author:Ravi Dubey
@date:09/23/2017
 *******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
//#include "platform.h"



uint8_t* my_memmove(uint8_t* src, uint8_t* dst, size_t length){

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
	uint8_t* temp_ptr = (uint8_t*)malloc(length );
	if (temp_ptr      == NULL) {
#ifdef ENABLE_LOWLEVEL_FUNCTION
		printf("Malloc Failed\n");
#endif


		return NULL;}
	size_t i;

	for(i = 0; i < length; i++ ){
		*(temp_ptr + i) = *(src + i);
	}

	for(i = 0; i < length; i++ ){
		*(dst + i) = *(temp_ptr + i);
	}


	return dst;

}


uint8_t* my_memcopy(uint8_t* src, uint8_t* dst, size_t length){

	//Null source or destination pointer
	if (src == NULL) {
#ifdef ENABLE_LOWLEVEL_FUNCTION
		printf("Invalid Source Address, memcopy aborted\n");
#endif


		return dst;
	}

	if (dst == NULL) {
#ifdef ENABLE_LOWLEVEL_FUNCTION
		printf("Invalid destination Address, memcopy aborted\n");
#endif


		return dst;
	}

	//Length =<0
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

	size_t i;

	for(i = 0; i < length; i++ ){
		*(dst + i) = *(src + i);
	}
#ifdef ENABLE_LOWLEVEL_FUNCTION
	printf("%zu elements copied succesfully\n",length );
#endif


	return dst;
}


uint8_t* my_memset(uint8_t* src, size_t length , uint8_t value){

	//Null source or destination pointer
	if (src == NULL) {
#ifdef ENABLE_LOWLEVEL_FUNCTION
		printf("Invalid Source Address, memset aborted\n");
#endif


		return src;
	}

	//Length <=0
	if(length <= 0) {
#ifdef ENABLE_LOWLEVEL_FUNCTION
		printf("Invalid Length. memset aborted\n");
#endif


		return src;
	}
	size_t i;
	for(i = 0; i < length; i++){

		*(src + i) = value ;
	}
#ifdef ENABLE_LOWLEVEL_FUNCTION
	printf("%zu elements set succesfully\n",length );
#endif


	return src;

}


uint8_t* my_memzero(uint8_t* src, size_t length){
	//Null source or destination pointer
	if (src == NULL) {
#ifdef ENABLE_LOWLEVEL_FUNCTION
		printf("Invalid Source Address, memzero aborted\n");
#endif


		return src;
	}

	//Length =0
	if(length <= 0) {
#ifdef ENABLE_LOWLEVEL_FUNCTION
		printf("Invalid length. memzero aborted\n");
#endif


		return src;
	}
	size_t i;
	for(i = 0; i < length; i++){

		*(src + i) = 0 ;
	}
#ifdef ENABLE_LOWLEVEL_FUNCTION
	printf("%zu elements set succesfully\n",length );
#endif


	return src;

}


uint8_t* my_reverse(uint8_t* src, size_t length){

	if (src == NULL) {
#ifdef ENABLE_LOWLEVEL_FUNCTION
		printf("Invalid Source Address, memreverse aborted\n");
#endif


		return src;
	}

	//Length <=0
	if(length <= 0) {
#ifdef ENABLE_LOWLEVEL_FUNCTION
		printf("Invalid length. memreverse aborted\n");
#endif


		return src;
	}

	uint8_t* temp_ptr = (uint8_t*)malloc(1);
	if (temp_ptr == NULL) {
#ifdef ENABLE_LOWLEVEL_FUNCTION
		printf("Malloc Failed\n");
#endif


		return NULL;}

	size_t i=0;
	while( (src + i)  <  (src + length - 1 - i) ){

		*temp_ptr = *(src + length  -1 - i);
		*(src + length  -1 - i) = *(src + i);
		*(src + i) = *temp_ptr;
		i++;
	}
	return src;
}


int32_t* reserve_words(size_t length){

	int32_t* ptr;
	uint8_t word_size = sizeof(int32_t*);//size of a word in bytes.
	ptr = (int32_t*)malloc(length * word_size);
	if (ptr == NULL) {
#ifdef ENABLE_LOWLEVEL_FUNCTION
		printf("Malloc Failed\n");
#endif
	}
#ifdef ENABLE_LOWLEVEL_FUNCTION
	else {
		printf("%zu bytes of Memory reserved\n", length * word_size);
	}
#endif
	return ptr;

}


void free_words(int32_t* src ){
	if (src == NULL) {
#ifdef ENABLE_LOWLEVEL_FUNCTION
		printf("NULL Source Address\n");
#endif
	}
	else {
		free(src);
#ifdef ENABLE_LOWLEVEL_FUNCTION
		printf("Memory Freed succesfully\n");
#endif
	}
}
