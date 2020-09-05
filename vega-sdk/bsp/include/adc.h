
#ifndef ADC_H_
#define ADC_H_



/*  Include section
*
***************************************************/

/*  Defines section
*


***************************************************/


#include "stdlib.h"	//for datatypes
#include "config.h"	//for datatypes



typedef struct
{
	UI address_reg;
	UI status_reg ;
	UI data_reg;
}ADCReg_type;


#define A0	0
#define A1	1
#define A2	2
#define A3	3


#define ADC_BASE_ADDRESS 	0x10001000
#define ADCReg (*((volatile ADCReg_type *)ADC_BASE_ADDRESS))


/*  Function declarations
*
***************************************************/

 
UI adc_analogRead(UC adc_channel_number);



#endif /* ADC_H_ */
