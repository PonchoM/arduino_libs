/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
 /**
 * @author Alexander Entinger, MSc
 * @brief test sketch for testing the multiple byte read single write functionality of the pc8570 i2c library
 * @file read_write_multiple.ino
 */

#include <PCF8570.h>
#include <Wire.h>

PCF8570 ram(0x50); // instantiate ram object, als address pins are tied to ground

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));

  // write a byte to each address and read it from that address back
  uint8_t const max_adr = 255;

  // fill a part of the memory with ascending numbers
  uint8_t data[16] = {0};
  uint8_t i=0; for(; i<16; i++) { data[i] = i; }
  uint8_t const adr = 45;
  ram.write_to_ram(adr, data, 16);
  
  // read the memory using single read
  Serial.println("Reading using single read");
  uint8_t adr_cnt=adr; 
  for(; adr_cnt<adr+16; adr_cnt++) {
    // read from adr
    uint8_t read_from = 0;
    ram.read_from_ram_single(adr_cnt, &read_from);
    // write result to serial
    char buf[32];
    uint8_t const length = sprintf(buf, "Adr: %d => %d\n", adr_cnt, read_from);
    Serial.write((uint8_t*)(buf), length);
  }
  
  // read the memory using multiple read
  Serial.println("Reading using multiple read");
  uint8_t read_data[16] = {0};
  ram.read_from_ram(adr, read_data, 16);
  for(adr_cnt=adr; adr_cnt<adr+16; adr_cnt++) {
    char buf[32];
    uint8_t const length = sprintf(buf, "Adr: %d => %d\n", adr_cnt, read_data[adr_cnt-adr]);
    Serial.write((uint8_t*)(buf), length);
  }
  
}

void loop() {

}

