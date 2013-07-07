/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
 /**
  * @author Alexander Entinger, MSc
  * @brief firmware for testing the ArduinoEncoder Library
  * @file Encoder.ino
  */

#include "ArduinoEncoder.h"

// instantiate the encoders
Encoder enc1(ENCODER_1, FALL);
Encoder enc2(ENCODER_2, BOTH);

// prerequisite: make sure to connect D2 with D4 and D3 with D5
// these pins serve as signal generators to test the library
int const enc1_gen = 4;
int const enc2_gen = 5;

/**
 * @brief init stuff
 */
void setup() {
  // initiate random generator
  randomSeed(analogRead(0));
  // initiate stimuli pins
  pinMode(enc1_gen, OUTPUT);
  digitalWrite(enc1_gen, HIGH);
  pinMode(enc2_gen, OUTPUT);
  digitalWrite(enc1_gen, HIGH);
  // initiate serial
  Serial.begin(115200);
}

/**
 * @brief thats the infinite loop of the firmware
 */
void loop() {
  // generate stimulus for the encoders
  int const loop_iterations = random(100);
  for(int i=0; i<loop_iterations; i++) {
    // switch both stimuli pins to low
    digitalWrite(enc1_gen, LOW);
    digitalWrite(enc2_gen, LOW);
    delay(50); // wait some time (50 ms)
    // switch both stimuli pins to high
    digitalWrite(enc1_gen, HIGH);
    digitalWrite(enc2_gen, HIGH);
  }
  // read the encoders and send value to the pc
  char buf[40];
  size_t const length = sprintf(buf, "Enc1 = %d, Enc2 = %d\n", enc1.get_pulse_count(), enc2.get_pulse_count());
  Serial.write((uint8_t *)(&buf[0]), length);
}

