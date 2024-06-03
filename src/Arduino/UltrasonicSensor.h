#ifndef UltrasonicSensor_h
#define UltrasonicSensor_h

#include <Arduino.h>

class UltrasonicSensor {
  private:
    int triggerPin;
    int echoPin;

  public:
    void init(int triggerPin, int echoPin) {
      this->triggerPin = triggerPin;
      this->echoPin = echoPin;
      pinMode(triggerPin, OUTPUT);
      pinMode(echoPin, INPUT);
    }

    float getDistance() {
      // Clear the trigger pin
      digitalWrite(triggerPin, LOW);
      delayMicroseconds(2);

      // Generate a short pulse on the trigger pin
      digitalWrite(triggerPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(triggerPin, LOW);

      // Measure the time it takes for the pulse to be received
      unsigned long duration = pulseIn(echoPin, HIGH);

      // Calculate the distance based on the measured time
      // The speed of sound in air is approximately 343 m/s
      // We divide by 2 because sound travels round trip
      float distance = (duration * 0.0343) / 2;

      return distance;
    }
};

#endif
