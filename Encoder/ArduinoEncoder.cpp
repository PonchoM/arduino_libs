/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, MSc
 * @brief this module implements the ability to count the number of pulses provided by wheel encoders
 * @file ArduinoEncoder.cpp
 */

#include "ArduinoEncoder.h"
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>

/* PROTOTYPE SECTION */

void config_encoder_1(encoder_options const o);
void config_encoder_2(encoder_options const o);
uint16_t get_pulse_count_encoder_1();
uint16_t get_pulse_count_encoder_2();

/* ARDUINO WRAPPER */

/**
 * @brief Constructor
 * @param pin use ENCODER_1 to select pin D2, ENCODER_2 to select pin D3
 * @param options here you can determine wether rising or falling signal or a combination leads to an increase of the counter value
 */
Encoder::Encoder(encoder_pin const pin, encoder_options const options) : m_pin(pin) {
	if(m_pin == ENCODER_1) config_encoder_1(options);
	else if(m_pin == ENCODER_2) config_encoder_2(options);
	sei(); // activate interrupts
}
	
/**
 * @brief returns the number of pulses counted by the encoder and resets the counter
 */
int Encoder::get_pulse_count() {
	if(m_pin == ENCODER_1) get_pulse_count_encoder_1();
	else if(m_pin == ENCODER_2) get_pulse_count_encoder_2();
}

/* C IMPLEMENTATION */
	
// counters for counting the 
static volatile uint16_t cnt_encoder_1 = 0; // Pin D2
static volatile uint16_t cnt_encoder_2 = 0; // Pin D3

/**
 * @brief configures encoder 1
 * @param o options for that encoder
 */
void config_encoder_1(encoder_options const o) {
        PORTD |= (1<<2); // set pin to input with pull up
        DDRD &= ~(1<<2);
	if(o == RISE) EICRA |= (1<<ISC01) | (1<<ISC00);
	else if(o == FALL) EICRA |= (1<<ISC01);
	else if(o == BOTH) EICRA |= (1<<ISC00);
	EIMSK |= (1<<INT0);
	get_pulse_count_encoder_1(); // reset counter
}

/**
 * @brief configures encoder 2
 * @param o options for that encoder
 */
void config_encoder_2(encoder_options const o) {
        PORTD |= (1<<3); // set pin to input with pullup
        DDRD &= ~(1<<3);
	if(o == RISE) EICRA |= (1<<ISC11) | (1<<ISC10);
	else if(o == FALL) EICRA |= (1<<ISC11);
	else if(o == BOTH) EICRA |= (1<<ISC10);
	EIMSK |= (1<<INT1);
	get_pulse_count_encoder_2(); // reset counter
}

/**
 * @brief returns the number of pulses counted on encoder 1 and resets the counter
 */
uint16_t get_pulse_count_encoder_1() {
	uint16_t ret = 0;
	cli();
	ret = cnt_encoder_1;
	cnt_encoder_1 = 0;
	sei();
	return ret;
}

/**
 * @brief returns the number of pulses counted on encoder 2 and resets the counter
 */
uint16_t get_pulse_count_encoder_2() {
	uint16_t ret = 0;
	cli();
	ret = cnt_encoder_2;
	cnt_encoder_2 = 0;
	sei();
	return ret;
}

/**
 * ISR for INT0 (D2)
 */
ISR(INT0_vect) {
	cnt_encoder_1++;
}

/**
 * ISR for INT1 (D3)
 */
ISR(INT1_vect) {
	cnt_encoder_2++;
}
