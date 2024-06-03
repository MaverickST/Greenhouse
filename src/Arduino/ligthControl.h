#ifndef LightControl_h
#define LightControl_h

#include <Arduino.h>

class LightControl {
  private:
    int pin;
    int frequency;

  public:
    void init(int pwmPin, int defaultFrequency = 60) {
      pin = pwmPin;
      frequency = defaultFrequency;
      pinMode(pin, OUTPUT);
      setFrequency(defaultFrequency);
    }

    void setFrequency(int freq) {
      frequency = freq;
      // Calculate the timer divisor value for the desired frequency
      int divisor;
      if (freq == 60) {
        divisor = 256; // Default setting for 60 Hz
      } else {
        divisor = (16000000 / (freq * 256)) - 1;
      }
      // Configure the timer for the desired frequency
      switch(pin) {
        case 5:
        case 6:
          TCCR0B = (TCCR0B & 0b11111000) | (divisor & 0b00000111);
          break;
        case 9:
        case 10:
          TCCR1B = (TCCR1B & 0b11111000) | (divisor & 0b00000111);
          break;
        case 3:
        case 11:
          TCCR2B = (TCCR2B & 0b11111000) | (divisor & 0b00000111);
          break;
        default:
          Serial.println("Pin not compatible for PWM");
      }
    }

    void setDutyCycle(int dutyCyclePercent) {
      // Adjust duty cycle (from 0 to 100)
      if (dutyCyclePercent < 0) dutyCyclePercent = 0;
      if (dutyCyclePercent > 100) dutyCyclePercent = 100;
      // Convert percentage to a value from 0 to 255
      int dutyCycle = map(dutyCyclePercent, 0, 100, 0, 255);
      // Set the duty cycle on the PWM pin
      analogWrite(pin, dutyCycle);
    }
};

#endif
