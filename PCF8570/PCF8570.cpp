/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module implements the control of an PCF8570 I2C RAM by arduino
 * @file PCF8570.cpp
 */
 
#include "PCF8570.h"

/**
 * @brief Constructor
 */
PCF8570::PCF8570(uint8_t const dev_address) : m_dev_address(dev_address) {
	Wire.begin();
}
	
/**
 * @brief writes multiple bytes to the i2c ram
 * @param address address where the data has to be written (auto increment after each byte)
 * @param data pointer to the array containing the data
 * @param length number of bytes to write
 * @return number of bytes written
 */
uint8_t PCF8570::write_to_ram(uint8_t const address, uint8_t const *data, uint8_t const length) {
	Wire.beginTransmission(m_dev_address);
	Wire.write(address);
	uint8_t bytes_written = 0;
	for(; (bytes_written < length) && (address+bytes_written)<255; bytes_written++) Wire.write(data[bytes_written]);
	Wire.endTransmission();
	return bytes_written;
}

/**
 * @brief reads multiple bytes from the i2c ram
 * @param address address from where the data has to be read (auto increment after each byte)
 * @param data pointer where the read data shall be stored
 * @param length number of bytes to read
 * @return number of bytes read
 */
uint8_t PCF8570::read_from_ram(uint8_t const address, uint8_t *data, uint8_t const length) {
	Wire.beginTransmission(m_dev_address);
	Wire.write(address);
	Wire.endTransmission();
	Wire.requestFrom(m_dev_address, length);
	uint8_t bytes_read = 0;
	for(; Wire.available() > 0; bytes_read++) data[bytes_read] = Wire.read();
	return bytes_read;
}
