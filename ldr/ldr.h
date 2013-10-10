/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module implements a small library for interfacing an ldr
 * @file ldr.h
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#ifndef LDR_H_
#define LDR_H_
 
#include <Arduino.h>

class ldr {
public:
	/**
	 * @brief Constructor
	 * @param pin number of the pin where the ldr is connected to
	 */
	ldr(int const pin);
	
	/**
	 * @brief returns the voltage measured at the ldr pin
	 */
	float get_voltage();
	
private:
	int m_pin;
};

#endif