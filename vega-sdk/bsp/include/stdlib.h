/*****************************************************************************

 Project Name		: MDP - Microprocessor Development Project
 Project Code		: HD083D
 Created		: 07-Nov-2019
 Filename		: stdlib.h
 Purpose		: Generic library functions
 Description		: Provides generic library functions like 
			  printf/memcpy etc 
 Author(s)		: Premjith A V
 Email			: premjith@cdac.in
    
 See LICENSE for license details.
******************************************************************************/


#ifndef INCLUDE_STDLIB_H_
#define INCLUDE_STDLIB_H_

#include <time.h>


typedef unsigned char  UC;	//1 Byte
typedef unsigned int   UI;	//4 Bytes
typedef unsigned long  UL;	//4 Bytes
typedef unsigned short US;	//2 Bytes

int printf(const char* fmt, ...);
int putchar(int ch);
int delay(unsigned int count);
int udelay(unsigned int count);
clock_t get_time();


#endif /* INCLUDE_STDLIB_H_ */
