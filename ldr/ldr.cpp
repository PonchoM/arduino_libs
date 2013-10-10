/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module implements a small library for interfacing an ldr
 * @file ldr.cpp
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */
 
#include "ldr.h"

/**
 * @brief Constructor
 * @param pin number of the pin where the ldr is connected to
 */
ldr::ldr(int const pin) 
	: m_pin(pin) {
	
}
	
/**
 * @brief returns the voltage measured at the ldr pin
 */
float ldr::get_voltage() {
	return ((float)(analogRead(m_pin))*5.0/1024.0);
}