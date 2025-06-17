#include "Arduino.h"

#ifndef SWITCH_H
#define SWITCH_H

class Switch
{
private:
    uint8_t pin;
public:
    Switch(uint8_t pin) {
        this->pin = pin;
        pinMode(this->pin, INPUT_PULLUP);
    };
    bool getState(uint8_t wait = 0) {
        if (delay > 0) {
            if (!digitalRead(this->pin) == LOW) { return LOW; }
            delay(wait);
            bool val = !digitalRead(this->pin);
            if (!val) {
                Serial.println("oh no");
            }
            return val;
        } else {
            return !digitalRead(this->pin);
        }
    };
};

#endif