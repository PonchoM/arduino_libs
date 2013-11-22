/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this library can be used to convert the value read from a ntc via an adc to convert to degrees
 * @file NTCLib.h
 * @license CC BY-SA 3.0 (http://creativecommons.org/licenses/by-sa/3.0/deed.de)
 */

#ifndef NTCLIB_H_
#define NTCLIB_H_
 
#include "Arduino.h"

class NTCLib {
public:
	/**
	 * @brief converts from the 10 - Bit ADC-Value to the temperature
	 */
	static int16_t convert(uint16_t const adc_value);

private:
	/**
	 * @brief Constructor is private, cant create objects from this class
	 */
	NTCLib() { }
};

#endif
