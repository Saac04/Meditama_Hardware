#include "claseUdp.h"
#include <string>
#define ssid "POCO_NSFW"
#define contrasenya "bromitanomas"
#define Sensor_Out_Pin 34  // Using GPIO 34 for vibration sensor


claseUdp conexion;

const int numReadings = 10;  // Reduced for faster response
int readings[numReadings];
int readIndex = 0;
long total = 0;
int average = 0;

int threshold = 0;
const int calibrationTime = 5000; // 5 seconds for calibration

unsigned long lastPrintTime = 0;
const unsigned long printInterval = 100; // Print every 100ms

// Variables to track max, min, and average vibration
int maxVibration = 0;
int minVibration = 4095; // Adjusted for the maximum ADC value of ESP32
long totalVibration = 0;
int vibrationCount = 0; 

void setup() {
  pinMode(Sensor_Out_Pin, INPUT);
  Serial.begin(115200);

  conexion.declararWifiSSID_Y_Contrasenya(ssid, contrasenya);
  conexion.declararCanal(9989);
  conexion.setupCliente();

  Serial.println("Calibrating sensor...");
  calibrateSensor();
  Serial.println("Calibration complete. Monitoring vibrations...");
}

void calibrateSensor() {
  long startTime = millis();
  int maxReading = 0;
  int minReading = 4095;  // Max value for ESP32's ADC is 4095

  while (millis() - startTime < calibrationTime) {
    int reading = analogRead(Sensor_Out_Pin);
    maxReading = max(maxReading, reading);
    minReading = min(minReading, reading);  // Update the minimum reading
  }

  threshold = (maxReading + minReading) / 2;  // Use mid-point as threshold
  Serial.print("Calibrated threshold: ");
  Serial.println(threshold);
}

void loop() {
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(Sensor_Out_Pin);
  total = total + readings[readIndex];
  readIndex = (readIndex + 1) % numReadings;

  average = total / numReadings;

  // Calculate vibration intensity
  int vibrationIntensity = abs(readings[readIndex] - average);

  // Update min, max, and calculate overall average vibration
 /* if (vibrationIntensity > 0) {
    maxVibration = max(maxVibration, vibrationIntensity);
    minVibration = min(minVibration, vibrationIntensity);  // Use the updated 4095
    totalVibration += vibrationIntensity;
    vibrationCount++;
  }*/

    // Condition for "Hi! I'm good for now ^^" if vibration doesn't surpass 50
 if (vibrationIntensity < 2550) {
    // Print this message once every 3 seconds if vibration is low
    if (millis() - lastPrintTime >= 3000) {
      Serial.println("Hi! I'm good for now ^^");
      conexion.enviarStringACliente("4");
      

      lastPrintTime = millis();
    }
  }


  
  // Condition for "!!! That hurts, stop ToT !!!" if vibration surpasses 3650
  else if (vibrationIntensity > 3569) {
    Serial.println("!!! That hurts... ToT !!!");

    conexion.enviarStringACliente("1");

  }
  // Condition for "Hey, that makes me dizzy @m@ " if vibration is around 1030
  else {
    Serial.println("Hey, that makes me dizzy @m@ ");
    conexion.enviarStringACliente("2");

  }
  // Detect significant vibrations above the threshold
  /*else if (vibrationIntensity > threshold) {
    Serial.print("Significant vibration detected! Intensity: ");
    Serial.println(vibrationIntensity);
    digitalWrite(LED_Pin, HIGH);
    delay(100);  // Reduced for faster response
    digitalWrite(LED_Pin, LOW);
  }
  
  // Print vibration level and stats at regular intervals if not in the above conditions
  else if (vibrationIntensity > 0) {
    // Print vibration level and stats at regular intervals
    if (millis() - lastPrintTime >= printInterval) {
      int avgVibration = (vibrationCount > 0) ? totalVibration / vibrationCount : 0;

      Serial.print("Vibration level: ");
      Serial.println(vibrationIntensity);
      
      Serial.print("Current Max Vibration: ");
      Serial.println(maxVibration);

      Serial.print("Current Min Vibration: ");
      Serial.println(minVibration);

      Serial.print("Current Average Vibration: ");
      Serial.println(avgVibration);

      lastPrintTime = millis();
    }
  }*/

  delay(1);
}