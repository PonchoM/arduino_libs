/**
 * @author Alexander Entinger, MSc / LXRobotics GmbH
 * @brief this library acts as an interface to the tpa81 thermopile array sensor
 * @file tpa81.h
 * @license CC BY-SA 4.0 http://creativecommons.org/licenses/by-sa/4.0/deed.de
 */

#ifndef TPA81_H_
#define TPA81_H_

#include "Arduino.h"

#define TPA81_DEFAULT_ADDRESS		(0xD0>>1)

class tpa81 {
public:
  /**
   * @brief Constructor
   */
  tpa81(uint8_t const address = TPA81_DEFAULT_ADDRESS);
  /**
   * @brief initializes the library
   */
  void begin();
  /**
   * @brief returns the software revision
   */
  uint8_t get_software_revision();
  /**
   * @brief returns the ambient temperature
   */
  uint8_t get_ambient_temperature();
  /**
   * @brief returns the temperature of all pixels
   * @param data contains the temperature of the pixels 1 to 8, data[0] = temperature of pixel 1, data[1] = temperature of pixel 2, ..., user has to guarantee that the pointer points to an array of size 8
   */
  boolean get_pixels(uint8_t *data);
  /**
   * @brief sets the servo position, value has to be between 0 and 31
   * @param pos servo position : pwm width = pos*60+540uS
   */
  void set_servo_position(uint8_t const pos);

private:
  uint8_t m_address;
};

#endif

