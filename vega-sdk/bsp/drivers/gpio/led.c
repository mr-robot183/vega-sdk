/***************************************************************************
 * Project                               :  MDP
 * Name of the file                      :  led.c
 * Brief Description of file             :  Driver to control the LEDs.
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
#include <include/gpio.h>
#include <include/led.h>
#include <include/config.h>


/** @fn on_LED
  @brief Write 1 to LED at GPIO pin.
  @details  Turn on LED connected at pin_no.
  @warning 
  @param[in] unsigned short pin_no
  @param[Out] No output parameter.
*/
void on_LED(US pin_no) {
	GPIO_write_pin(pin_no,ON_LED); // Lit LED at pin_no.
	return;
}

/** @fn off_LED
 * @brief  Write 0 to LED at GPIO pin.
 * @details  Turn off LED connected at pin_no.
 * @warning 
 * @param[in] unsigned short pin_no
 * @param[Out] No output parameter.
*/
void off_LED(US pin_no) {
	GPIO_write_pin(pin_no,OFF_LED); // Turn off LED at pin_no.
	return;
}


/** @fn read_switch
 * @brief  Read GPIO pin value.
 * @details Read the GPIO pin value by setting the direction as OUTPUT.
 * @warning 
 * @param[in] unsigned short: pin_no
 * @param[Out] Return the status of pin.
*/
US read_switch(US pin_no) {
	US sw_status = 0;	
	sw_status = GPIO_read_pin(pin_no); // Read the pin status.
	return sw_status;
}



