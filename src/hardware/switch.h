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
    bool getState() {
        return !digitalRead(this->pin);
    };
};

#endif