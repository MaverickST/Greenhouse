#ifndef RGBLED_h
#define RGBLED_h

#include <Arduino.h>

class RGBLED {
  private:
    int redPin;
    int greenPin;
    int bluePin;

  public:
    void init(int redPin, int greenPin, int bluePin) {
      this->redPin = redPin;
      this->greenPin = greenPin;
      this->bluePin = bluePin;

      pinMode(redPin, OUTPUT);
      pinMode(greenPin, OUTPUT);
      pinMode(bluePin, OUTPUT);
    }

    void setColor(bool redValue, bool greenValue, bool blueValue) {
      digitalWrite(redPin, redValue ? HIGH : LOW);
      digitalWrite(greenPin, greenValue ? HIGH : LOW);
      digitalWrite(bluePin, blueValue ? HIGH : LOW);
    }

    void turnOff() {
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, LOW);
    }
};

#endif
