/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @file ArduinoUART.h
 * @description hardware uart
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "ArduinoUART.h"

// Prototypes
uint8_t HardIncrPtr(uint8_t ptr);

// Receive Ringbuffer
static volatile uint8_t RX_BUF[RX_SIZE];
static volatile uint8_t RX_Head = 0;
static volatile uint8_t RX_Tail = 0;
static volatile uint8_t RX_N = 0;
// Transmit Ringbuffer
static volatile uint8_t TX_BUF[RX_SIZE];
static volatile uint8_t TX_Head = 0;
static volatile uint8_t TX_Tail = 0;
static volatile uint8_t TX_N = 0;


/**
 * @brief initialization of the software uart
 * @brief desired baudrate (use defines from header file)
 */
void UART_Init(uint8_t const baudrate) {
  UCSR0A |= (1<<U2X0);    // double read / write speed
  UCSR0B |= (1<<RXCIE0) | // enable the receive interrupt
  (1<<RXEN0)  | // enable receiver
  (1<<TXEN0);   // enable transmitter
  UBRR0 = baudrate;
}

/**
 * @brief access received data byte from the rx ring buffer
 * @return data byte
 */
uint8_t UART_GetByte() {
  uint8_t tmp = 0;
  cli();
  if(RX_N > 0) {
    tmp = RX_BUF[RX_Tail];
    RX_Tail = HardIncrPtr(RX_Tail);
    RX_N--;
  }
  sei();
  return tmp;
}

/**
 * @brief returns true if date is available, false otherwise
 */
bool UART_IsDataAvailable() {
  cli();
  bool const dataAvailable = (RX_N != 0);
  sei();
  return dataAvailable;
}

/**
 * @brief write an array of bytes in the ringbuffer for transmission
 * @param data pointer to the data array to write to the serial device
 * @param size number of elements to write to the seriel device
 */
void UART_WriteBytes(uint8_t const *data, uint8_t const size) {
  uint8_t i = 0;
  cli();
  for(; i < size; i++) { 
    if(TX_N < TX_SIZE) {
      TX_BUF[TX_Head] = data[i];
      TX_N++;
      TX_Head = HardIncrPtr(TX_Head);
    }
  }
  sei();
  UCSR0B |= (1<<UDRIE0); // enable transmission by enabling the uart data register empty interrupt
}

/**
 * @brief increments pointers of the ringbuffer
 */
uint8_t HardIncrPtr(uint8_t const ptr) {
  uint8_t const tmp = ptr + 1;
  if(tmp == RX_SIZE) { 
    return 0;   
  }
  else 			   { 
    return tmp; 
  }
}

/**
 * @brief interrupt service routine for receiving data
 */
ISR(USART_RX_vect) {
  if(RX_N < RX_SIZE) {
    RX_BUF[RX_Head] = UDR0;
    RX_N++;
    RX_Head = HardIncrPtr(RX_Head);
  }
}

/**
 * @brief interrupt service routine for transmitting data
 */
ISR(USART_UDRE_vect) {
  if(TX_N > 0) {
    UDR0 = TX_BUF[TX_Tail];
    TX_Tail = HardIncrPtr(TX_Tail);
    TX_N--;
  }
  // disable interrupt if all data is transmitted
  if(TX_N == 0) { 
    UCSR0B &= ~(1<<UDRIE0); 
  } 
}

