#include <Arduino.h>
// the library ltr329, and i2c should be installed before
#include "ltr_329.h"
const int LED_Red_Pin = 1;           //Led_Rot
const int LED_Board_Status_Pin = 7;  //Board Satus Led
const int LED_Green_Pin = 22;        //Led_Grün
const int LED_Yellow_Pin = 21;       //Led_Gelb
const int Buzzer =0; //Buzzer
static LTR_329_measurement measurement = { 0 };

void setup() {
  Serial.begin(115200);
  while (!Serial);
  pinMode(LED_Board_Status_Pin, OUTPUT);
  pinMode(LED_Red_Pin, OUTPUT);
  pinMode(LED_Green_Pin, OUTPUT);
  pinMode(LED_Yellow_Pin, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  LTR_329_init();
  LTR_329_setGain(LTR_329_GAIN_4X);  // 4X Gain suitable for the low level light, such as in door light
}

void loop() {
  digitalWrite(LED_Board_Status_Pin, HIGH);
  LTR_329_readMeasurement(&measurement);
  uint16_t value_channel0 = measurement.channel0;
  uint16_t value_channel1 = measurement.channel1;
  uint16_t illuminance= (value_channel0 + value_channel1) / 2;
  if(illuminance>51)
  {
    digitalWrite(LED_Red_Pin, HIGH);
    digitalWrite(LED_Green_Pin, LOW);
    digitalWrite(Buzzer, HIGH);
    Serial.println(illuminance);
    Serial.println("Something happened. Beware of being attacked!");
  }
  else 
  {
    digitalWrite(LED_Green_Pin, HIGH);
    digitalWrite(LED_Red_Pin, LOW);
    Serial.println(illuminance);
    digitalWrite(Buzzer, LOW);
  }
  delay(100);
}
