#include <Wire.h>

const int hallSensorPin = 4;         // Pin connected to the BU52011 Hall sensor
const int LED_Red_Pin = 1;           //Led_Rot
const int LED_Board_Status_Pin = 7;  //Board Satus Led
const int LED_Green_Pin = 22;        //Led_Grün
const int LED_Yellow_Pin = 21;       //Led_Gelb
const int Buzzer = 0;
const unsigned long buzzerDuration = 2000;
void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;  // Wait for serial monitor to open
  pinMode(LED_Board_Status_Pin, OUTPUT);
  pinMode(LED_Red_Pin, OUTPUT);
  pinMode(LED_Green_Pin, OUTPUT);
  pinMode(LED_Yellow_Pin, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(hallSensorPin, INPUT);  // Set the hall sensor pin as input
}

void loop() {
  int magnetState = digitalRead(hallSensorPin);  // Read the state of the hall sensor
  digitalWrite(LED_Board_Status_Pin, HIGH);
  //Based on Datasheet if there ist magnet field present state will be Low
  if (magnetState == LOW) {
    Serial.println("Magnet detected, Beware of being attacked!");
    digitalWrite(LED_Red_Pin, HIGH);
    digitalWrite(LED_Green_Pin, LOW);
    digitalWrite(Buzzer, HIGH);
  } else {
    Serial.println("No Attack Detected");
    digitalWrite(Buzzer, LOW);
    digitalWrite(LED_Red_Pin, LOW);
    digitalWrite(LED_Green_Pin, HIGH);
  }
  delay(50);
}
