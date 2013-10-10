/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module reads the voltage from the ldr pin and transmit it to the pc
 * @file ldr_read_voltage.ino
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#include <ldr.h>

// instantiate object
ldr myLDR(0);

void setup() {
  Serial.begin(115200);
}

void loop() {
  delay(1000);
  float const ldr_voltage = myLDR.get_voltage();
  Serial.print("V_LDR = ");
  Serial.print(ldr_voltage);
  Serial.print("\n");  
}
