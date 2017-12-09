/********************************************************************************
@file:conversion.h
@brief:An abstraction for conversion operations implemented in conversion.c

This file provides definitions for functions and external variables of file
conversion.c
@author:Ravi Dubey
@date:09/23/2017
 ********************************************************************************/


#ifndef FILE_CONVERSION
#define FILE_CONVERSION

#include <stdint.h>
#include "common.h"
/********************************************************************************
@brief:Implements Integer to ASCII conversion

This function converts data from standard Integer type(base 2 to 16) into an ASCII
string and store it in the given memory location.
@param:Integer to be converted to ASCII, BASE, Pointer to location to store converted
value.
@return:length of the converted data. -1 in case of error
 ********************************************************************************/
uint8_t my_itoa(int32_t, uint8_t*, uint32_t);


/********************************************************************************
@brief:Implements ASCII to Integer conversion

This function converts data from ASCII to standard Integer type(base 2 to 16)
@param:Pointer to ascii string to be converted, Length of the ascii string, Base of
converted integer
@return: Converted Integer Value. -1 in case of error.
 ********************************************************************************/
int32_t my_atoi( uint8_t*, uint8_t , uint32_t);


/********************************************************************************
@brief:Implements Big to Little Endian conversion

This function converts array of data in memory from a Big Endian representation to
a Little Endian.
@param:Pointer to data, Length of data in bytes.
@return: 1 on Success, -1 if fails.
 ********************************************************************************/
int8_t big_to_little32( uint32_t*, uint32_t);


/********************************************************************************
@brief:Implements Little to Big Endian conversion

This function converts array of data in memory from a Little Endian representation
to Big Endian.
@param:Pointer to data, Length of data in bytes.
@return: 1 on Success, -1 if fails.
 ********************************************************************************/
int8_t little_to_big32( uint32_t*, uint32_t);

#endif
