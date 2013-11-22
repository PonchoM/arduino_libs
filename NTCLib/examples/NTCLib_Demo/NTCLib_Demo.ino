/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this sketch demos how to use the ntc library, for further details see lxrobotics.com/blog (TODO: Insert correct link here)
 * @NTCLib_Demo.ino
 */

#include "NTCLib.h"

int const ntc_adc_pin = 3; // in case of the LXR Tubeclock Shield the NTC is connected to the pin A3

void setup() {
  Serial.begin(115200);
}

void loop() {
  int const temperature = NTCLib::convert(analogRead(ntc_adc_pin));
  Serial.println(temperature, DEC);
  delay(250);
}
