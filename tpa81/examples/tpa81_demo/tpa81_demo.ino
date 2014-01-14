/**
 * @author Alexander Entinger, MSc / LXRobotics GmbH
 * @brief this file demonstrates how to use the tpa81 library to interface with an tpa81 sensor
 * @file tpa81_demo.ino
 * @license CC BY-SA 4.0 http://creativecommons.org/licenses/by-sa/4.0/deed.de
 */

#include "tpa81.h"
#include "Wire.h" // dont forget this line

tpa81 thermo_sensor; // instantiate sensor with default address

void setup() {
  thermo_sensor.begin();
  Serial.begin(115200);
  Serial.print("TPA81 Software Revision: ");
  Serial.println(thermo_sensor.get_software_revision());
  // set the servo pwm to 1.5 ms pulse duration
  thermo_sensor.set_servo_position(16);
}

void loop() {
  uint8_t ambient_temperature = thermo_sensor.get_ambient_temperature();
  Serial.print("Ambient Temperature = ");
  Serial.println(ambient_temperature);
  uint8_t pixel_temp[8];
  if(thermo_sensor.get_pixels(pixel_temp)) {
    for(int i=0; i<8; i++) {
     Serial.print("Pixel ");
     Serial.print(i+1);
     Serial.print(" Temperature = ");
     Serial.println(pixel_temp[i]);
    }
  } else {
    Serial.println("Failed to read pixel temperature"); 
  }
  delay(1000);
}
