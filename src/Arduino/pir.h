#ifndef PIR_h
#define PIR_h

#include <Arduino.h>

class PIR {
  private:
    int pin;
    bool motion;

  public:
    void init(int sensorPin) {
      pin = sensorPin;
      pinMode(pin, INPUT);
    }

    bool motionDetected() {
      motion = digitalRead(pin);
      return motion;
    }
};

#endif