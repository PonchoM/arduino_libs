/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
 /**
  * @author Alexander Entinger
  * @brief Firmware file for the arduino sensboard
  * @file test_srf02.pde
  */

#include <Serial.h>
#include <Wire.h>
#include "SRF02.h"

// Arduino analog input 4 = I2C SDA
// Arduino analog input 5 = I2C SCL 

#define DELAY_TIME_MS (500)

// instantiate sensors
SRF02 srf02_sensor(SRF02_DEFAULT_DEVICE_ADDR, SRF02_CENTIMETERS);

/**
 * @brief init stuff
 */
void setup() {
	// open serial port at 9600 Baud
	Serial.begin(9600); 
	// initialize I2C
	Wire.begin(); 
}

/**
 * @brief thats the infinite loop of the firmware
 */
void loop() {
 
	srf02_sensor.StartRanging();
	delay(DELAY_TIME_MS);
	uint16_t const distance = srf02_sensor.GetDistance();
	Serial.println(distance);

}

