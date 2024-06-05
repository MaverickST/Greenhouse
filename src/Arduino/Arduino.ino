#include "ldr.h"
#include "soilMoisture.h"
#include "pir.h"
#include "rgbLED.h"
#include "ligthControl.h"
#include "UltrasonicSensor.h"

#include <DHT.h>
#include <PID_v1.h>

#define LDR_PIN A0
#define SOIL_MOISTURE_PIN A1
#define PIR_PIN 2
#define DHT_PIN 4
#define DHT_TYPE DHT11
#define ULTRASONIC_TRIGGER_PIN 7
#define ULTRASONIC_ECHO_PIN 8

#define RGB_RED_PIN 3
#define RGB_GREEN_PIN 5
#define RGB_BLUE_PIN 6

#define LIGHT_CONTROL_PIN 10
#define LIGHT_CONTROL_FREQUENCY 60

#define VCC 5.0

#define SETPOINT_LUX 50.0  // Setpoint for light intensity
#define TANK_HIGH 10 // cm

// Sensor instances
LDR sensor_ldr;
SoilMoisture sensor_soilMoisture;
PIR sensor_pir;
UltrasonicSensor sensor_ultrasonic;

// Actuator instances
RGBLED rgbLed;
LightControl lightControl;
DHT dht(DHT_PIN, DHT_TYPE);

// PID control variables
double pid_setpoint, pid_input, pid_output;
PID myPID(&pid_input, &pid_output, &pid_setpoint, 2.0, 5.0, 1.0, DIRECT);

void printAllData(float luz, float agua, float humedadTierra, float humedadAmbiente, float temperatura, int presencia);

void setup() {
  Serial.begin(9600);

  // Initialize sensors
  sensor_ldr.init(LDR_PIN, VCC);
  sensor_soilMoisture.init(SOIL_MOISTURE_PIN, VCC);
  sensor_pir.init(PIR_PIN);
  rgbLed.init(RGB_RED_PIN, RGB_GREEN_PIN, RGB_BLUE_PIN);
  lightControl.init(LIGHT_CONTROL_PIN, LIGHT_CONTROL_FREQUENCY);
  dht.begin();
  sensor_ultrasonic.init(ULTRASONIC_TRIGGER_PIN, ULTRASONIC_ECHO_PIN);

  // Initialize PID
  pid_setpoint = SETPOINT_LUX;
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 100);  // Limit PID output to 0-100
}

void loop() {
  // Read sensors
  pid_input = sensor_ldr.readLuxes();
  float soilMoisturePercent = sensor_soilMoisture.readPercent();
  bool motionDetected = sensor_pir.motionDetected();
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float distance = sensor_ultrasonic.getDistance();
  float tank_level = (distance / TANK_HIGH) * 100;

  // Compute PID
  myPID.Compute();

  // Set light intensity based on PID output
  lightControl.setDutyCycle((int)pid_output);

  // Water Tank RGB light
  if (tank_level <= 30) {
    rgbLed.setColor(1, 0, 0); // Red
  } else if (tank_level <= 60) {
    rgbLed.setColor(1, 1, 0); // Yellow
  } else {
    rgbLed.setColor(0, 1, 0); // Green
  }

  // Print sensor values
  printAllData(pid_input, tank_level, soilMoisturePercent, humidity, temperature, motionDetected);

}

void printAllData(float luz, float agua, float humedadTierra, float humedadAmbiente, float temperatura, int presencia) {
  Serial.print("L");
  Serial.print(luz);
  
  Serial.print("A");
  Serial.print(agua);
  
  Serial.print("HT");
  Serial.print(humedadTierra);
  
  Serial.print("HA");
  Serial.print(humedadAmbiente);
  
  Serial.print("T");
  Serial.print(temperatura);
  
  Serial.print("P");
  Serial.print(presencia);
  
  Serial.println("X");
}
