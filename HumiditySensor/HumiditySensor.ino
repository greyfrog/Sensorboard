#include <Wire.h>
const int LED_Red_Pin = 1;           // Led_Rot
const int LED_Board_Status_Pin = 7;  // Board Satus Led
const int LED_Green_Pin = 22;        // Led_Grün
const int LED_Yellow_Pin = 21;       // Led_Gelb
const int Buzzer = 0;                // Buzzer
#define SHTC3_ADDR 0x70              // I2C address of the SHTC3 sensor

void setup() {
  Wire.begin();          // Initialize the I2C communication
  Serial.begin(115200);  // Initialize the serial communication
  while (!Serial)
    ;
  Serial.println("SHTC3 Sensor is reading");
  pinMode(LED_Board_Status_Pin, OUTPUT);
  pinMode(LED_Red_Pin, OUTPUT);
  pinMode(LED_Green_Pin, OUTPUT);
  pinMode(LED_Yellow_Pin, OUTPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop() {
  digitalWrite(LED_Board_Status_Pin, HIGH);
  digitalWrite(LED_Green_Pin, HIGH);
  static float previousHumidity = readHumidity();
  float currentHumidity = readHumidity();
  float HumidityChange = currentHumidity - previousHumidity;
  Serial.print("Humidity change: ");
  Serial.print(HumidityChange);
  Serial.println(" %");

  Serial.print("Humidity: ");
  Serial.print(currentHumidity);
  Serial.println(" %");
  if (abs(HumidityChange) > 1 || currentHumidity>60) {
    digitalWrite(LED_Red_Pin, HIGH);
    digitalWrite(LED_Green_Pin, LOW);
    Serial.println("Something happened. Be aware of being attacked.");
    activateAlarm();
  } else {
    digitalWrite(LED_Red_Pin, LOW);
    digitalWrite(LED_Green_Pin, HIGH);
  }
  previousHumidity = currentHumidity;
  delay(500);
}

float readHumidity() {
  // Request humidity and temperature measurement
  uint16_t cmdWakeup = 0x3517;  // 16-bit command code

  Wire.beginTransmission(SHTC3_ADDR);
  Wire.write((cmdWakeup >> 8) & 0xFF);  // Send the most significant byte
  Wire.write(cmdWakeup & 0xFF);         // Send the least significant byte
  Wire.endTransmission();
  delay(5);                     // Wait for Power up
  uint16_t cmdLPMode = 0x5C24;  // 16-bit command code
  Wire.beginTransmission(SHTC3_ADDR);
  Wire.write((cmdLPMode >> 8) & 0xFF);  // Send the most significant byte
  Wire.write(cmdLPMode & 0xFF);         // Send the least significant byte
  Wire.endTransmission();
  delay(15);  // Wait for measurement to complete
  // Read measurement data
  Wire.requestFrom(SHTC3_ADDR, 6);
  if (Wire.available() >= 6) {
    uint16_t humidity = 0x0000;
    uint16_t temp = 0x0000;

    uint8_t msbHumidity = Wire.read();
    uint8_t lsbHumidity = Wire.read();
    uint8_t crcHumidity = Wire.read();
    // uint8_t msbTemp = Wire.read();
    // uint8_t lsbTemp = Wire.read();
    // uint8_t crcTemp = Wire.read();

    humidity = ((uint16_t)msbHumidity << 8) | lsbHumidity;
    // temp = ((uint16_t)msbTemp << 8) | lsbTemp;

    // Convert to actual values
    float humidityPercent = 100 * ((float)humidity / 65535.0);
    // float temperatureC = -45 + 175 * ((float)(temp & 0xFFFC) / 65536.0);

    return humidityPercent;
  }
  return 0.0;
}

void activateAlarm() {
  digitalWrite(Buzzer, HIGH);
  delay(500);
  digitalWrite(Buzzer, LOW);
}