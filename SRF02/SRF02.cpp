/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger
 * @brief Source file for using the SRF02 ultra sonic range finder
 * @file SRF02.cpp
 */

#if ARDUINO >= 100
  #include <Arduino.h>  // for 1.0 and later
#else
  #include <WProgram.h> // for earlier releases
#endif
#include "SRF02.h"
#include <Wire.h>

// result register
#define RESULT_REGISTER		(0x02)
// commmand register
#define COMMAND_REGISTER	(0x00)

/**
 * @brief SRF02 CTor, initializing SRF02 with address and mode
 * @param ard I2C Device address
 * @param mode ranging mode
 */
SRF02::SRF02(unsigned char addr, unsigned char mode) {
	// assign values
	mAddress = addr;
	mMode = mode;
	mStartTime = 0;
}

/**
 * @brief start us ranging of the sensor
 */
void SRF02::StartRanging() {
	// save current system time
	mStartTime = millis();
	// start I2C transmission
  	Wire.beginTransmission(mAddress);
	// write to the command register (0x00)
	Wire.write((unsigned char)COMMAND_REGISTER);
	// write the mode (real ranging mode)
	// (see to defines)
	Wire.write(mMode);	
	// stop I2C transmission
	Wire.endTransmission();
}

/**
 * @brief get value from the sensor
 * @return 0 in case of an error, distance in the desired ranging mode otherwise
 */
unsigned int SRF02::GetDistance() {
	unsigned int result = 0;
	unsigned long EndTime = millis();

	if((EndTime - mStartTime) < TIME_PER_MEASUREMENT_MS) {
		return SRF02_ERROR; // to less time for correct ranging
	}
	else {
		// prepare the requestment of the result
		// start I2C transmission
		Wire.beginTransmission(mAddress);
		// send adress of result register
		Wire.write(RESULT_REGISTER);
		// end I2C transmission
		Wire.endTransmission();
		
		// fetch the result
		// send I2C request for data (2 Bytes)
		Wire.requestFrom(mAddress,(unsigned char)2);
		// wait for 2 bytes to return
		while (Wire.available() < 2 )   {
		}
		// read the two bytes and combine to one
		result = Wire.read() << 8;
		result = result + Wire.read();
		return result;
	}
}
