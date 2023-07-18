#include <Arduino.h>

#include "ltr_329.h"

static LTR_329_measurement measurement = { 0 };

void setup() {
  Serial.begin(9600);

  LTR_329_init();
  LTR_329_setGain(LTR_329_GAIN_4X);
}

void loop() {
  LTR_329_readMeasurement(&measurement);

  Serial.print("LTR-329 channel 0 data: ");
  Serial.println(measurement.channel0);
  Serial.print("LTR-329 channel 1 data: ");
  Serial.println(measurement.channel1);

  delay(1000);
}