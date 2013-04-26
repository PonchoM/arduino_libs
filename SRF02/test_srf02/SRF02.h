/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
 /**
 * @author Alexander Entinger
 * @brief Header file for using the SRF02 ultra sonic range finder
 * @file SRF02.h
 */

#ifndef SRF02_H
#define SRF02_H

// ranging modes
#define SRF02_INCHES       			(0x50)
#define SRF02_CENTIMETERS  			(0x51)
#define SRF02_MICROSECONDS 			(0x52)
// needed amount of time to do one complete range measurement
#define TIME_PER_MEASUREMENT_MS 	(100)
// error code for srf 02
#define SRF02_ERROR 				(0)
// default device address
#define SRF02_DEFAULT_DEVICE_ADDR 	(0x70) 
// result register
#define RESULT_REGISTER    			(0x02)

/**
 * @brief class SRF02
 * for using the arduino with a SRF02 Devantech ultrasonic distance sensor
 */
class SRF02 {
public:
	/**
     * @brief SRF02 CTor, initializing SRF02 with address and mode
	 * @param ard I2C Device address
	 * @param mode ranging mode
	 */
	SRF02(unsigned char addr, unsigned char mode);
	
	/**
     *@brief start ranging of the sensor
	 */
	void StartRanging();

	/**
     * @brief get value from the sensor
     * @return 0 in case of an error, distance in the desired ranging mode otherwise
     */
	unsigned int GetDistance();

private:
	unsigned char mAddress;		// address of the sensor
	unsigned char mMode;		// ranging mode
	unsigned long mStartTime;	// start time of a ranging, needed
								// to proceed with correct sensor values
};

#endif