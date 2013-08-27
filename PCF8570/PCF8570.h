/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module implements the control of an PCF8570 I2C RAM by arduino
 * @file PCF8570.h
 */
 
 #ifndef _PCF8570_H_
 #define _PCF8570_H_
 
 #include <Arduino.h>
 #include <Wire.h>
 
 class PCF8570 {
 public:
	/**
	 * @brief Constructor
	 */
	PCF8570(uint8_t const dev_address);
	
	/**
	 * @brief writes multiple bytes to the i2c ram
	 * @param address address where the data has to be written (auto increment after each byte)
	 * @param data pointer to the array containing the data
	 * @param length number of bytes to write
	 * @return number of bytes written
	 */
	uint8_t write_to_ram(uint8_t const address, uint8_t const *data, uint8_t const length);
	
	/**
	 * @brief writes a single byte to the i2c ram
 	 * @param address address where the data has to be written
	 * @param data byte to be written to the i2c ram
	 * @return true in case of success, false in case of failure
	 */
	bool write_to_ram_single(uint8_t const address, uint8_t const data) {
		return (write_to_ram(address, &data, 1) == 1);
	}
	
	/**
	 * @brief reads multiple bytes from the i2c ram
	 * @param address address from where the data has to be read (auto increment after each byte)
	 * @param data pointer where the read data shall be stored
	 * @param length number of bytes to read
	 * @return number of bytes read
	 */
	uint8_t read_from_ram(uint8_t const address, uint8_t *data, uint8_t const length);
	
	/**
	 * @brief reads a single byte from the i2c ram
	 * @param address address from where the data has to be read
	 * @param pointer to the variable, where the read byte should be stored
	 * @return true in case of success, false in case of failure
	 */
	bool read_from_ram_single(uint8_t const address, uint8_t *data) {
		return (read_from_ram(address, data, 1) == 1);
	}	 
 
 private:
	uint8_t m_dev_address; 
 };
 
 #endif