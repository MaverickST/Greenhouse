#ifndef SoilMoisture_h
#define SoilMoisture_h

#include <Arduino.h>

class SoilMoisture {
  private:
    int pin;
    float Vcc;

  public:
    void init(int sensorPin, float vcc = 3.3) {
      pin = sensorPin;
      if (vcc < 3.3) {
        Serial.println("Warning: Supply voltage below the minimum allowed. It will be adjusted to the minimum value.");
        Vcc = 3.3;
      } else if (vcc > 5.0) {
        Serial.println("Warning: Supply voltage above the maximum allowed. It will be adjusted to the maximum value.");
        Vcc = 5.0;
      } else {
        Vcc = vcc;
      }
    }

    int read() {
      int analogValue = analogRead(pin);
      return analogValue;
    }

    float readPercent() {
      int analogValue = analogRead(pin);
      float moisturePercent = map(analogValue, 0, 1023, 0, 100);
      return moisturePercent;
    }
};

#endif
