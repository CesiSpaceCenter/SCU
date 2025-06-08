#include "Arduino.h"

#ifndef BUZZER_H
#define BUZZER_H

class Buzzer {
private:
    uint8_t pin;
    bool state = false;
    uint32_t lastOn;
    uint32_t lastOff;
    void on();
    void off();
public:
    Buzzer(uint8_t pin);
    void beep(uint16_t duration, uint8_t repeat);
    void loop();
    bool enabled = false;
    uint16_t onTime = 100;
    uint16_t offTime = 100;
};

#endif