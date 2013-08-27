/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
 /**
 * @author Alexander Entinger, MSc
 * @brief test sketch for testing the single read single write functionality of the pc8570 i2c library
 * @file read_write_single.ino
 */

#include <PCF8570.h>
#include <Wire.h>

PCF8570 ram(0x50); // instantiate ram object, als address pins are tied to ground

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));

  // write a byte to each address and read it from that address back
  uint8_t const max_adr = 255;

  uint8_t adr=0; 
  for(; adr<max_adr; adr++) {
    // store a random nomber between 0 and 255 at the given adre
    uint8_t const to_write = (uint8_t)(random(256));
    ram.write_to_ram_single(adr, to_write);
    // read from adr
    uint8_t read_from = 0;
    ram.read_from_ram_single(adr, &read_from);
    // write result to serial
    char buf[64];
    uint8_t const length = sprintf(buf, "Adr: %d => W: %d => R: %d\n", adr, to_write, read_from);
    Serial.write((uint8_t*)(buf), length);
  }
}

void loop() {

}

