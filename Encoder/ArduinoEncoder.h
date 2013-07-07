/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, MSc
 * @brief this module implements the ability to count the number of pulses provided by wheel encoders
 * @file ArduinoEncoder.cpp
 */
 
#ifndef ARDUINOENCODER_H_
#define ARDUINOENCODER_H_

#include "Arduino.h"

typedef enum {ENCODER_1, ENCODER_2} encoder_pin; // ENCODER_1 = D2, ENCODER_2 = D3
typedef enum {RISE, FALL, BOTH} encoder_options;

class Encoder {
public:
	/**
	 * @brief Constructor
	 * @param pin use ENCODER_1 to select pin D2, ENCODER_2 to select pin D3
	 * @param options here you can determine wether rising or falling signal or a combination leads to an increase of the counter value
	 */
	Encoder(encoder_pin const pin, encoder_options const options);
	
	/**
	 * @brief Destructor
	 */
	~Encoder() { };
	
	/**
	 * @brief returns the number of pulses counted by the encoder and resets the counter
	 */
	int get_pulse_count();
	
private:
	encoder_pin m_pin;
	
};

#endif