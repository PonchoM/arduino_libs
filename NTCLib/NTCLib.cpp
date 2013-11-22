/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this library can be used to convert the value read from a ntc via an adc to convert to degrees
 * @file NTCLib.cpp
 * @license CC BY-SA 3.0 (http://creativecommons.org/licenses/by-sa/3.0/deed.de)
 */

#include "NTCLib.h"

static int16_t const start_temp = -55;		// at what temp value does the table start
static int16_t const temp_step_size = 5;	// whats the step size from one value to the next
static uint8_t const table_size = 42;
static uint16_t const table[table_size] = {
  1008,
  1002,
  994,
  983,
  970,
  954,
  933,
  909,
  879,
  845,
  807,
  763,
  717,
  667,
  615,
  563,
  512,
  461,
  413,
  368,
  327,
  289,
  255,
  224,
  197,
  173,
  152,
  133,
  117,
  103,
  91,
  80,
  71,
  63,
  56,
  49,
  44,
  39,
  35,
  31,
  28,
  25
};

/**
 * @brief converts from the 10 - Bit ADC-Value to the temperature
 */
int16_t NTCLib::convert(uint16_t const adc_value) {
  for(int16_t i=1; i<table_size; i++) {
    if(table[i-1] > adc_value && table[i] < adc_value) {
      float const diff_temp = (float)(temp_step_size);
      float const diff_val = (float)(table[i]) - (float)(table[i-1]);
      float const k = diff_temp/diff_val;
      float const d = (float)(i*temp_step_size + start_temp) - k * (float)(table[i]);
      return ((int16_t)((float)(adc_value) * k + d));
    }
  }
  return 0;
}

