

/***************************************************
* Module name: main.c
*
* Copyright 2020 Company CDAC(T)
* All Rights Reserved.
*
*  The information contained herein is confidential
* property of Company. The user, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Company.
*
*
* Module Description:
* SPI test pgm
*
***************************************************/

/*  Include section
*
*
***************************************************/

#include "stdlib.h"
#include "config.h"
#include "timer.h"
#include "interrupt.h"



/** @fn main
 * @brief Generate a delay in polling mode.
 * @details In this pgm the timers0,timers1 & timers2 are loaded with values and enabled.
 * @warning 
 * @param[in] No input parameter 
 * @param[Out] No output parameter 
*/
void main ()
{

	//Initialise interrupt controller
	initialize_interrupt_table();

	printf("\n\r TIMER TEST CASE - INTR Method");

	timer_run_in_intr_mode(TIMER_0,0x200);
	timer_run_in_intr_mode(TIMER_1,0x350);
	timer_run_in_intr_mode(TIMER_2,0x500);

	interrupt_enable(7); // For TIMER 0
	interrupt_enable(8); // For TIMER 1
	interrupt_enable(9); // For TIMER 2
	
	while(1);
	
}




