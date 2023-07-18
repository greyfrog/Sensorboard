#include <Wire.h>

const int IR_LED = 12;               //IR-Led
const int photodiode = 8;            //Photodiode
const int LED_Red_Pin = 1;           //Led_Rot
const int LED_Board_Status_Pin = 7;  //Board Satus Led
const int LED_Green_Pin = 22;        //Led_Grün
const int LED_Yellow_Pin = 21;       //Led_Gelb
const int Buzzer = 0; //Buzzer
void setup() {

  Serial.begin(115200);
  while (!Serial)
    ;  // Wait for serial monitor to open
  pinMode(LED_Board_Status_Pin, OUTPUT);
  pinMode(LED_Red_Pin, OUTPUT);
  pinMode(LED_Green_Pin, OUTPUT);
  pinMode(LED_Yellow_Pin, OUTPUT);
  pinMode(IR_LED, OUTPUT);  // Set the IR_LED pin as output
  pinMode(Buzzer, OUTPUT); 
  Serial.begin(9600);       // Start the serial communication for debugging
}

void loop() {
  digitalWrite(IR_LED, HIGH);
  if (digitalRead(photodiode) == LOW) {
    Serial.println("Light interruption. Beware of being attacked");
    digitalWrite(LED_Red_Pin, HIGH);
    digitalWrite(LED_Green_Pin, LOW);
    digitalWrite(Buzzer, HIGH);
  } else {
    Serial.println("No Attack Detected");
    digitalWrite(LED_Red_Pin, LOW);
    digitalWrite(LED_Green_Pin, HIGH);
    digitalWrite(Buzzer, LOW);
  }
  delay(100);
}
