/***************************************************************************
 * Project                               :  MDP
 * Name of the file                      :  spi.c
 * Brief Description of file             :  Driver to control the spi device.
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
#include <include/spi.h>
#include <include/config.h>

SPIcntrlRegType gSPItransfer;


/** @fn SPI_init
  @brief Initialize SPI controller.
  @details Initialise SPI with the default setting.
  @warning 
  @param[in]  unsigned char spi_number: Denotes the selected SPI.
  @param[Out] No output parameter 
*/

void SPI_init(UC spi_number) {

	UC rx = 0;
	UI reg_data = 0;

	SPIreg(spi_number).Baudrate = SPI_BAUD_CFD_16;		// Baud divisor

	gSPItransfer.Bits.Dbits = BPT_8;			// Bits per transfer set to 8.	
	gSPItransfer.Bits.CSAAT = LOW;				// CSAAT signal is low.

	gSPItransfer.Bits.SPIrxTxIntr = RX_TX_INTR_DIS;		// Both Rx & Tx interrupts disabled.

	gSPItransfer.Bits.Mode = SPI_MODE_0;			// Mode set as '0'.
	gSPItransfer.Bits.DataOrder = MSB;			// MSB bit is transferred first.
	gSPItransfer.Bits.Periph = 0;				// Peripheral type is Fixed peripheral.
	gSPItransfer.Bits.PeriphCS = 0;				// Peripheral chip select is '0'.

	SPIreg(spi_number).Control.hword = gSPItransfer.Value;	// Update value to register
	__asm__ __volatile__ ("fence");
	return;
}


/** @fn SPI_config
 @brief Customise the SPI controller's initialize setting.
 @details Read the details below.
 
SPI Control word details
************************
[15:13] Reserved R/W “000”
[12:9]  DBITS    R/W “0000”
 8:     CSAAT : ‘0’ Chip Select Active After Transfer When this bit is set, the chip select line remains active low until transfer to another peripheral is required, or this bit is cleared.
 7:     SPTIE : SPI Transmit Interrupt Enable.
	‘0’= Interrupt disabled.
	‘1’= Interrupt enabled.
	If enabled interrupt generated when data is loaded from SPI_TDR to Transmit Shift Register.


 6:	SPI Receive Interrupt Enable
	‘0’= Interrupt disabled.
	‘1’= Interrupt enabled.
	If enabled interrupt generated when data is loaded from Receive Shift Register to SPI_RDR
 5:   	CPOL R/W ‘0’ Clock Polarity .See table 1
 4:   	CPHA R/W ‘0’ Clock Phase. See table 1
 3:   	LSB/MSB First. This bit selects LSB/MSB first data transfer format.
	‘0’ = MSB first transfer format
	‘1’ = LSB first transfer format
 2: 	PS R/W ‘0’. 
	Fixed peripheral-0.
	Variable peripheral-1.
 1,0:   PCS1, PCS0 R/W ‘0’ Peripheral Chip select. Active only if PS is active. See table 2

Table 1
*******

SPI Clock configuration Modes
*****************************
-------------------------------------------------
| SPI-mode   |  CPOL(bit - 5)	|  CPHA(bit - 4)|	
-------------------------------------------------
|   0	     |	    0		|	0	|
|   1	     |	    0		|	1	|
|   2        |	    1		|	0	|
|   3	     |	    1		|	1	|
-------------------------------------------------


Table 2
*******

SPI Clock configuration Modes
*****************************
---------------------------------------------------------
| PCS1 (bit - 1) |     PCS1 (bit - 0)   |        CS     |	
---------------------------------------------------------
|   0	         |	    0		|	1110	|
|   0	         |	    1		|	1101	|
|   1            |	    0		|	1011	|
|   1	         |	    1		|	0111	|
---------------------------------------------------------

@warning 
 @param[in]  unsigned char spi_number: Denotes the selected SPI, 
             unsigned short cword: The control word to be written to SPI control register.
             for the selected SPI.
 @param[Out] No output parameter 

*/

void SPI_config(UC spi_number, US cword) {

	SPIreg(spi_number).Control.hword = cword;	// Update value to register
	__asm__ __volatile__ ("fence");
	return;
}

/** @fn SPI_set_baud
 @brief Set the baud frequency divider value to SPI controller baud register.
 @details 
-------------------------------------------------
| 	BAUD   		|  	CLk freq Divider |	
-------------------------------------------------
|     	0	     	|	    4		 |	
|   	1	     	|	    8		 |	
|   	2        	|	    16		 |	
|   	3		|	    32		 |
|	4		|	    64		 |		
|	5		|	    128		 |		
|	6		|	    256		 |
|	7		|	    512		 |
|	8		|	    1024	 |
|	9		|	    2048	 |
|	10-15	     	|	    reserved 	 |	
-------------------------------------------------
 @warning 
 @param[in]  unsigned char spi_number: Denotes the selected SPI, 
             unsigned char bBaudCFD: The baud frequency divisor value.
 @param[Out] No output parameter 
*/
void SPI_set_baud(UC spi_number,UC bBaudCFD) {

	SPIreg(spi_number).Baudrate = (bBaudCFD <<4);  //Set the baud frequency divider value
	__asm__ __volatile__ ("fence");
	return;
}

/** @fn SPI_get_slave_select
 @brief Read the slave select value.
 @details Read the slave select value at bit positions 16 and 17.
 @warning 
 @param[in] unsigned char spi_number: Denotes the selected SPI.
 @param[Out] slave select value as 32 bit data 
*/
UI SPI_get_slave_select(UC spi_number) {
	UI read_data = 0;

	read_data = SPIreg(spi_number).RxData;		// Read SPI RX data reg value.
	read_data = ((read_data & 0x30000) >> 16);	// Extract the value at bit positions 16 & 17.
	return read_data;
}

/** @fn SPI_set_slave_select
 @brief Write the slave select value.
 @details Write the slave select value at bit positions 16 and 17.
 @warning 
 @param[in] unsigned char spi_number: Denotes the selected SPI.
            unsigned int slave_sel_val: The Slave select bits.
 @param[Out] No output parameter
*/
void SPI_set_slave_select(UC spi_number ,UI slave_sel_val) {

	UI write_data = 0,read_data = 0;
	read_data = SPIreg(spi_number).TxData;
	write_data = read_data | (slave_sel_val << 16);	
	SPIreg(spi_number).TxData  = write_data;
	return;
}

/** @fn SPI_check_overrun
 @brief  Checks for overrun
 @details Checks if overrun occurred or not by reading SPI controller's status register.
 @warning 
 @param[in] unsigned char spi_number: Denotes the selected SPI.
 @param[Out] returns 1 if overrun occurs otherwise 0. 
*/
UC SPI_check_overrun(UC spi_number)
{
	UC status = 0;

	status = SPIreg(spi_number).Status;
	if(status & (1<<5))
		return 1;
	else
		return 0;
}

/** @fn SPI_enable_intr
 @brief  Enable SPI interrupts.
 @details Enable the SPI tx and Rx interrupt.
 @warning 
 @param[in] unsigned char spi_number: Denotes the selected SPI, 
            unsigned char tx_intr: 1 to enable tx intr, 0 to disable tx intr.
            unsigned char rx_intr: 1 to enable tx intr, 0 to disable tx intr.
 @param[Out] No output parameter 
*/
void SPI_enable_intr(UC spi_number,UC tx_intr,UC rx_intr)
{
	UC intr_val = 0;
	US cword = 0;

	cword = SPIreg(spi_number).Control.hword;
	intr_val = ((tx_intr << 7) | (rx_intr << 6));
	cword |= intr_val;
	SPIreg(spi_number).Control.hword = cword;
	__asm__ __volatile__ ("fence");
	return;
}

/** @fn SPI_receive
 @brief  Read data.
 @details Read data (16 bit) received in Read data register of SPI controller.
 @warning 
 @param[in] unsigned char spi_number: Denotes the selected SPI
 @param[Out] read data as 16 bit value. 
*/
US SPI_receive(UC spi_number)
{
	US bRxData;
	UC status = 0;
	
	while(!((SPIreg(spi_number).Status) & SPI_RX_COMPLETE_BIT));	//  Waiting for RX complete bit to set.
	bRxData = SPIreg(spi_number).RxData;				//  Read data.
	return bRxData;
}

/** @fn SPI_transmit
 @brief  Write data.
 @details Writes data (16 bit) to transmit data register of SPI controller.
 @warning 
 @param[in] unsigned char spi_number: Denotes the selected SPI, 
            unsigned short bData: The data to be written to tx data register.
 @param[Out] No output parameter. 
*/
void SPI_transmit(UC spi_number,US bData) {

	SPI_wait_if_busy(spi_number);					// Checking if SPI controller is busy or not. Waits if busy.
	while (!(SPIreg(spi_number).Status & SPI_TX_HOLD_EMPTY_BIT));	// Check Tx Hold empty bit is set or not. If not wait here.
	SPIreg(spi_number).TxData = bData;				// Write the data (can be a command or actual data to be written to spi device)
	__asm__ __volatile__ ("fence");
	return;
}


/** @fn SPI_0_intr_handler
 @brief  Interrupt handler.
 @details Reads SPI controllers status register to distinguish which type of interrupt has occurred.
 @warning 
 @param[in] No input parameter.
 @param[Out] No output parameter. 
*/
void SPI_0_intr_handler(void) {
	UC status = 0;

	status = SPIreg(0).Status;	//Read SPI 0 status register.
	if(status & (1 << 2)) // SPI receive complete interrupt occurred.
	{
		//spi_handle_rx_intr(); // Funcion pointer for rx intr.
	}
	else if(status & (1 << 3))  // SPI TX register empty interrupt occurred.
	{
		//spi_handle_tx_intr(); // Funcion pointer for tx intr.
	}   
}


/** @fn SPI_1_intr_handler
 @brief  Interrupt handler.
 @details Reads SPI controllers status register to distinguish which type of interrupt has occurred.
 @warning 
 @param[in] unsigned char spi_number: Denotes the selected SPI.
 @param[Out] No output parameter. 
*/
void SPI_1_intr_handler(void) {
	UC status = 0;

	status = SPIreg(1).Status;	//Read SPI 1 status register.
	if(status & (1 << 2)) // SPI receive complete interrupt occurred.
	{
		//spi_handle_rx_intr(); // Funcion pointer for rx intr.
	}
	else if(status & (1 << 3))  // SPI TX register empty interrupt occurred.
	{
		//spi_handle_tx_intr(); // Funcion pointer for tx intr.
	}   
}


/** @fn SPI_2_intr_handler
 @brief  Interrupt handler.
 @details Reads SPI controllers status register to distinguish which type of interrupt has occurred.
 @warning 
 @param[in] unsigned char spi_number: Denotes the selected SPI.
 @param[Out] No output parameter. 
*/
void SPI_2_intr_handler(void) {
	UC status = 0;

	status = SPIreg(2).Status; //Read SPI 2 status register.
	if(status & (1 << 2)) // SPI receive complete interrupt occurred.
	{
		//spi_handle_rx_intr(); // Funcion pointer for rx intr.
	}
	else if(status & (1 << 3))  // SPI TX register empty interrupt occurred.
	{
		//spi_handle_tx_intr(); // Funcion pointer for tx intr.
	}   
}

/** @fn SPI_wait_if_busy
 @brief  Checks if SPI controller is busy.
 @details Reads SPI controllers status register to check its busy status. Waits here untill it becomes free.
 @warning 
 @param[in] unsigned char spi_number: Denotes the selected SPI
 @param[Out] No output parameter.
*/
void SPI_wait_if_busy(UC spi_number) {

	while (SPIreg(spi_number).Status & SPI_BUSY_BIT); // Read SPI controller status register to check if its busy or not.
	return ;   
}


/** @fn SPI_set_CSAAT_pin
 @brief  Set CSAAT pin high/low.
 @details Sets Chip Select Active After Transfer pin high : This pin must be high when the command/data is more than one byte
 and pin must be lowered when the command/data is over.
 @warning 
 @param[in] unsigned char spi_number: Denotes the selected SPI, 
            unsigned char status: 1 - to make CSAAT pin high, 0 - to make CSAAT pin low.
 @param[Out] No output parameter.
*/
void SPI_set_CSAAT_pin(UC spi_number, UC status) {

	if(status == 1)
		SPIreg(spi_number).Control.hword |= (1 << 8);	// Setting CSAAT bit high.
	else
		SPIreg(spi_number).Control.hword &= ~(1 << 8);	// Setting CSAAT bit low.
	__asm__ __volatile__ ("fence");
	return ;   
}




/** @fn SPI_read_rx_reg
 @brief  Read data.
 @details Read data (16 bit) received in Read data register of SPI controller.
 @warning 
 @param[in] unsigned char spi_number: Denotes the selected SPI.
 @param[Out] read data as 16 bit value. 
*/
US SPI_read_rx_reg(UC spi_number)
{
	US bRxData;
	bRxData = SPIreg(spi_number).RxData;	// Read SPI data reg value.
	return bRxData;
}

/** @fn SPI_write_tx_reg
 @brief  Write data.
 @details Writes data (16 bit) to transmit data register of SPI controller.
 @warning 
 @param[in] unsigned char spi_number: Denotes the selected SPI,
            unsigned short bData: The data to be written to tx data register.
 @param[Out] No output parameter. 
*/
void SPI_write_tx_reg(UC spi_number,US bData) {

	SPI_wait_if_busy(spi_number);					// Checking if SPI controller is busy or not. Waits if busy.
	while (!(SPIreg(spi_number).Status & SPI_TX_HOLD_EMPTY_BIT));	// Check Tx Hold empty bit is set or not. If not wait here.
	SPIreg(spi_number).TxData = bData;				// Write the data (can be a command or actual data to be written to spi device)
	__asm__ __volatile__ ("fence");
	return;
}

