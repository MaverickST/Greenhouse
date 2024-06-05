#ifndef LightControl_h
#define LightControl_h

#include <Arduino.h>

class LightControl {
  private:
    int pin;
    int frequency;

    void setTimerRegisters(int prescalerBits, int timerCounts) {
      switch(pin) {
        case 5:
          TCCR0A = 0; // Reset the registers
          TCCR0B = 0; // Reset the registers
          TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0B1); // Fast PWM, non-inverting mode
          TCCR0B |= prescalerBits; // Set the prescaler
          OCR0B = timerCounts; // Set the compare value
          break;
        case 6:
          TCCR0A = 0; // Reset the registers
          TCCR0B = 0; // Reset the registers
          TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0A1) | (1 << COM0B1); // Fast PWM, non-inverting mode for both channels
          TCCR0B |= prescalerBits; // Set the prescaler
          OCR0A = timerCounts; // Set the compare value for channel A
          OCR0B = timerCounts; // Set the compare value for channel B
          break;
        case 9:
          TCCR1A = 0; // Reset the registers
          TCCR1B = 0; // Reset the registers
          TCCR1A |= (1 << WGM10) | (1 << COM1A1); // Fast PWM, non-inverting mode
          TCCR1B |= (1 << WGM12) | prescalerBits; // Set the prescaler
          OCR1A = timerCounts; // Set the compare value
          break;
        case 10:
          TCCR1A = 0; // Reset the registers
          TCCR1B = 0; // Reset the registers
          TCCR1A |= (1 << WGM10) | (1 << COM1B1); // Fast PWM, non-inverting mode
          TCCR1B |= (1 << WGM12) | prescalerBits; // Set the prescaler
          OCR1B = timerCounts; // Set the compare value
          break;
        case 3:
          TCCR2A = 0; // Reset the registers
          TCCR2B = 0; // Reset the registers
          TCCR2A |= (1 << WGM20) | (1 << WGM21) | (1 << COM2B1); // Fast PWM, non-inverting mode
          TCCR2B |= prescalerBits; // Set the prescaler
          OCR2B = timerCounts; // Set the compare value
          break;
        case 11:
          TCCR2A = 0; // Reset the registers
          TCCR2B = 0; // Reset the registers
          TCCR2A |= (1 << WGM20) | (1 << WGM21) | (1 << COM2A1) | (1 << COM2B1); // Fast PWM, non-inverting mode for both channels
          TCCR2B |= prescalerBits; // Set the prescaler
          OCR2A = timerCounts; // Set the compare value for channel A
          OCR2B = timerCounts; // Set the compare value for channel B
          break;
        default:
          Serial.println("Pin not compatible for PWM");
      }
    }

  public:
    void init(int pwmPin, int defaultFrequency = 30) {
      pin = pwmPin;
      frequency = defaultFrequency;
      pinMode(pin, OUTPUT);
      setFrequency(frequency);
    }

    void setFrequency(int freq) {
      // Determine the appropriate prescaler value and bit settings based on the desired frequency
      int prescalerBits;
      long timerCounts = F_CPU / (2 * freq); // Use F_CPU macro for clock speed

      if (timerCounts < 256) {
        prescalerBits = 1; // No prescaler
      } else if (timerCounts < 2048) {
        prescalerBits = 2; // Prescaler 8
        timerCounts /= 8;
      } else if (timerCounts < 16384) {
        prescalerBits = 3; // Prescaler 64
        timerCounts /= 64;
      } else if (timerCounts < 65536) {
        prescalerBits = 4; // Prescaler 256
        timerCounts /= 256;
      } else {
        prescalerBits = 5; // Prescaler 1024
        timerCounts /= 1024;
      }

      if (timerCounts > 255) timerCounts = 255; // Limit to 8-bit value

      // Configure the timer for the desired frequency
      setTimerRegisters(prescalerBits, timerCounts);
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
