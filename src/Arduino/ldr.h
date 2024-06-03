#ifndef LDR_H
#define LDR_H

#include <Arduino.h>

class LDR {
  private:
    int pin;                       // Analog pin to which the LDR is connected
    float Vcc;                    // Supply voltage
    const float R0 = 10.0 * 1000; // Resistance at I0 (e.g., 10 kΩ at 100 lux)
    const float E0 = 100.0;       // Reference illuminance (100 lux)
    const float gamma = 0.7;      // Photoresistor constant

  public:
    void init(int pinNumber, float vcc = 5.0) {
      pin = pinNumber;
      Vcc = vcc;
      pinMode(pin, INPUT); // Configure the pin as input
    }

    float readLuxes() {
      // Read the analog value (0-1023)
      int analogValue = analogRead(pin);
      // Convert to voltage (0-Vcc)
      float voltage = analogValue * (Vcc / 1023.0);
      
      // Calculate the resistance of the LDR
      float resistance = 0;
      if (voltage != 0) {
        // Calculate the resistance of the LDR
        const float R_ref = 10000.0;  // Known reference resistance (10kΩ)
        resistance = (Vcc * R_ref) / (Vcc - voltage);
      }
      
      // Calculate luxes using the potential relationship
      float luxes = 0;
      if (resistance != 0) {
        luxes = E0 * pow((R0 / resistance), (1 / gamma));
      }
      
      return luxes;
    }
};

#endif
