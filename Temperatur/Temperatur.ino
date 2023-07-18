#include <Wire.h>

const int LED_Red_Pin = 1;           // Led_Rot
const int LED_Board_Status_Pin = 7;  // Board Satus Led
const int LED_Green_Pin = 22;        // Led_Grün
const int LED_Yellow_Pin = 21;       // Led_Gelb
const int Buzzer = 0;                // Buzzer
#define TMP112_ADDR 0x4A             // I2C address of TMP112 ADD0 connected to SDA line

void setup() {
  Wire.begin();
  Serial.begin(115200);
  while (!Serial);
  Serial.println("TMP112 Sensor Reading");
  pinMode(LED_Board_Status_Pin, OUTPUT);
  pinMode(LED_Red_Pin, OUTPUT);
  pinMode(LED_Green_Pin, OUTPUT);
  pinMode(LED_Yellow_Pin, OUTPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop() {
  digitalWrite(LED_Board_Status_Pin, HIGH);
  digitalWrite(LED_Green_Pin, HIGH);
  static float previousTemperature = readTemperature();

  float currentTemperature = readTemperature();

  // count the difference
  float temperatureChange = currentTemperature - previousTemperature;

  // Output in Console
  Serial.print("Temperature change: ");
  Serial.print(temperatureChange);
  Serial.println(" °C");
  Serial.print("Current Temperature: ");
  Serial.print(currentTemperature);
  Serial.println(" °C");

  // Check the conditions
  if (currentTemperature > 40 || abs(temperatureChange) >= 5) {
    activateAlarm();
    digitalWrite(LED_Red_Pin, HIGH);
    digitalWrite(LED_Green_Pin, LOW);
    Serial.println("Beware of being attacked");
  }
  else if (abs(temperatureChange) > 2 && abs(temperatureChange)< 5 || currentTemperature >32) {
    digitalWrite(LED_Yellow_Pin, HIGH);
    digitalWrite(LED_Green_Pin, LOW);
    digitalWrite(LED_Red_Pin, LOW);
    Serial.println("Something happened, be aware");
  }
  else {
    digitalWrite(LED_Yellow_Pin, LOW);
    digitalWrite(LED_Red_Pin, LOW);
    digitalWrite(LED_Green_Pin, HIGH);
  }

  // Update the value
  previousTemperature = currentTemperature;

  delay(1000);
}

float readTemperature() {
  Wire.beginTransmission(TMP112_ADDR);
  Wire.write(0x00);  // Register Address
  Wire.endTransmission(false);

  Wire.requestFrom(TMP112_ADDR, 2);
  if (Wire.available() == 2) {
    uint16_t rawData = Wire.read() << 8 | Wire.read();

    // Convertion
    float temperature = (float)(rawData >> 4) * 0.0625;
    return temperature;
  }

  return 0.0;  // If wrong
}

void activateAlarm() {
  digitalWrite(Buzzer, HIGH);
  delay(500);
  digitalWrite(Buzzer, LOW);
}