/***************************************************************************
 * Project                               :  MDP
 * Name of the file                      :  interrupt.c
 * Brief Description of file             :  Driver to control the Interrupt.
 * Name of Author                        :  Sreeju G R
 * Email ID                              :  sreeju@cdac.in

  Copyright (C) 2020  CDAC(T). All rights reserved.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.

***************************************************************************/

#include <include/stdlib.h>
#include <include/interrupt.h>
#include <include/timer.h>
#include <include/config.h>
#include <include/encoding.h>


extern int INTERRUPT_Handler_0;
fp interrupt_table[64]; //Array of Function pointer.


/** @fn    enable_irq
  @brief   Enable processor interrupt and Global interrupt in machine mode.
  @details The function "set_csr" will set the interrupt bit in MIE register and Machine mode External interrupt in MSTATUS register.
  @warning
  @param[in]  No input parameter.
  @param[Out] No output parameter.
*/
void enable_irq(void) {
    set_csr(mie, MIP_MEIP);			// Set MEIE bit in MIE register for Machine External Intr.
    set_csr(mstatus, MSTATUS_MIE);		// Set global machine intr bit (3rd bit) in MSTATUS register.
}

/** @fn interrupt_enable
  @brief  Enable interrupt in controller.
  @details The interrupt enable register is set with the enable value of peripheral selected.
  @warning 
  @param[in] unsigned char intr_number: The number at which the periphral will interrupt
  @param[Out] No output parameter.
*/

void interrupt_enable(UC intr_number)
{
	intr_regs.INTR_EN |= (1 << intr_number);	// Enable interrupt for peripheral in interrupt controller.
	__asm__ __volatile__ ("fence");
}

 
/** @fn initialize_interrupt_table
 @brief  Write to MTVEC reg and initialize interrupt controller table for both 32 bit & 64 bit processors.
 @details Fill interrupt table with the address of peripheral interrupt handlers.
 @warning 
 @param[in]  No input parameter.
 @param[Out] No output parameter.
*/

void initialize_interrupt_table(void)
{
	enable_irq();	// Enable global interrupt and external interrupt of the processor.

#if __riscv_xlen == 64
	//For 64 Bit processors			
	write_csr(mtvec,(UL)&INTERRUPT_Handler_0);		// Set MTVEC register with vector address.
	interrupt_table[10] = timer0_intr_handler; 	// Timer0 interrupt numer is 10 for 64 bit processor.
	interrupt_table[11] = timer1_intr_handler; 	// Timer1 interrupt numer is 11 for 64 bit processor.
	interrupt_table[12] = timer2_intr_handler;	// Timer2 interrupt numer is 12 for 64 bit processor.
#else
	//For32 Bit processors
	write_csr(mtvec,(UI)&INTERRUPT_Handler_0);		// Set MTVEC register with vector address.
	interrupt_table[7] = timer0_intr_handler; 	// Timer0 interrupt numer is 7 for 64 bit processor.
	interrupt_table[8] = timer1_intr_handler; 	// Timer1 interrupt numer is 8 for 64 bit processor.
	interrupt_table[9] = timer2_intr_handler;	// Timer2 interrupt numer is 9 for 64 bit processor.
#endif
}

 
/** @fn interrupt_handler
 @brief  Invoke the peripheral interrupt handler.
 @details The interrupt controller's status register is read to identify the interrupted peripheral and then the corresponding
	  handler for the peripheral is invoked.
 @warning 
 @param[in] No input parameter.
 @param[Out] No output parameter.
*/
void interrupt_handler(void){

	UI intr_status = intr_regs.INTR_STATUS; 		// Read interrupt status register.

	for(int i = 0; i < 32; i++) 
	{
		if ((intr_status >> i) & 1)
			interrupt_table[i]();		// Invoke the peripheral handler as function pointer.
	}
}




