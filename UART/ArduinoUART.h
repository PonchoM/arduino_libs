/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @file ArduinoUART.h
 * @description hardware uart
 */

#ifndef ARDUINOUART_H
#define ARDUINOUART_H

#include <stdint.h>
#include <stdbool.h>

// defines for baudrate
#define BAUD115200 (16) // 2.1 % Error
#define BAUD76800  (25) // 0.2 % Error
#define BAUD57600  (34) // 0.8 % Error
#define BAUD38400  (51) // 0.2 % Error
#define BAUD9600   (207)// 0.2 % Error

// defines for buffer size of rx and tx buffer
#define RX_SIZE 16
#define TX_SIZE 64

/**
 * @brief initialization of the software uart
 * @brief desired baudrate (use defines from header file)
 */
void UART_Init(uint8_t const baudrate);

/**
 * @brief access received data byte from the rx ring buffer
 * @return data byte
 */
uint8_t UART_GetByte();

/**
 * @brief returns true if date is available, false otherwise
 */
bool UART_IsDataAvailable();

/**
 * @brief write an array of bytes in the ringbuffer for transmission
 * @param data pointer to the data array to write to the serial device
 * @param size number of elements to write to the seriel device
 */
void UART_WriteBytes(uint8_t const *data, uint8_t const size);

#endif

