/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
 /**
 * @author Alexander Entinger, BSc
 * @brief test file for testing the serial module, sends all received data back to the pc
 * @file UART.ino
 */

#include "ArduinoUART.h"

void setup() {
  UART_Init(BAUD115200);
  sei();
}

void loop() {
  if(UART_IsDataAvailable()) {
    uint8_t const data = UART_GetByte();
    UART_WriteBytes(&data, 1);     
  }
}
