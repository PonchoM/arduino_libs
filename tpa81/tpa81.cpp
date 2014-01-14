/**
 * @author Alexander Entinger, MSc / LXRobotics GmbH
 * @brief this library acts as an interface to the tpa81 thermopile array sensor
 * @file tpa81.cpp
 * @license CC BY-SA 4.0 http://creativecommons.org/licenses/by-sa/4.0/deed.de
 */

#include "tpa81.h"
#include "Wire.h"

#define COMMAND_REG                     (0x00)
#define SOFTWARE_REVISION_REG		(0x00)
#define AMBIENT_TEMPERATURE_REG		(0x01)
#define PIXEL1_REG			(0x02)

#define MIN_SERVO_POS                   (0x00) // 0
#define MAX_SERVO_POS                   (0x1F) // 31

/**
 * @brief Constructor
 */
tpa81::tpa81(uint8_t const address) : 
m_address(address) {

}

/**
 * @brief initializes the library
 */
void tpa81::begin() { 
  Wire.begin();
}

/**
 * @brief returns the software revision
 */
uint8_t tpa81::get_software_revision() {
  Wire.beginTransmission(m_address);
  Wire.write(SOFTWARE_REVISION_REG);
  Wire.endTransmission();
  Wire.requestFrom(m_address, (uint8_t)(1));
  if(Wire.available() == 1) {
    return Wire.read();
  } 
  else {
    return 0;
  }
}

/**
 * @brief returns the ambient temperature
 */
uint8_t tpa81::get_ambient_temperature() {
  Wire.beginTransmission(m_address);
  Wire.write(AMBIENT_TEMPERATURE_REG);
  Wire.endTransmission();
  Wire.requestFrom(m_address, (uint8_t)(1));
  if(Wire.available() == 1) {
    return Wire.read();
  } 
  else {
    return 0;
  }
}

/**
 * @brief returns the temperature of all pixels
 * @param data contains the temperature of the pixels 1 to 8, data[0] = temperature of pixel 1, data[1] = temperature of pixel 2, ..., user has to guarantee that the pointer points to an array of size 8
 */
boolean tpa81::get_pixels(uint8_t *data) {
  Wire.beginTransmission(m_address);
  Wire.write(PIXEL1_REG);
  Wire.endTransmission();
  Wire.requestFrom(m_address, (uint8_t)(8));
  if(Wire.available() == 8) {
    for(uint8_t i=0; i<8; i++) data[i] = Wire.read();
    return true;
  } 
  else {
    return false;
  }
}

/**
 * @brief sets the servo position, value has to be between 0 and 31
 * @param pos servo position : pwm width = pos*60+540uS
 */
void tpa81::set_servo_position(uint8_t const pos) {
  if(pos >= MIN_SERVO_POS && pos <= MAX_SERVO_POS) {
    Wire.beginTransmission(m_address);
    Wire.write(COMMAND_REG);
    Wire.write(pos);
    Wire.endTransmission();
  }
}


