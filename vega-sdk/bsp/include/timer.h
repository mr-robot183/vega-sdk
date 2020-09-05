
#ifndef TIMER_H_
#define TIMER_H_



/*  Include section
*
***************************************************/

#include "stdlib.h"	//for datatypes
#include "config.h"	//for datatypes

/*  Defines section
*


***************************************************/


#define 	TIMER_0		0
#define 	TIMER_1		1
#define 	TIMER_2		2

typedef struct
{
	UI LoadCount;
	UI CurrentValue;
	UI Control;
	UI EOI;
	UI IntrStatus;
}TimerReg_type;


#define Timer(n) (*((volatile TimerReg_type *)(TIMER_BASE_ADDRESS + (n * 20))))

/*  Function declarations
*
***************************************************/

UC timer_put_delay(UC timer_no, UI no_of_clocks);
UI timer_get_current_value(UC timer_no);
 
 
void timer_run_in_intr_mode(UC timer_no, UI no_of_clocks);
void timer_unmask_intr(UC timer_no); 	
void timer_load(UC timer_no,UI count); 
void timer0_intr_handler(void); 	
void timer1_intr_handler(void);
void timer2_intr_handler(void);


#endif /* TIMER_H_ */
