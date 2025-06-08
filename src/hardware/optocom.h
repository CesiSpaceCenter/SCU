#include <Arduino.h>

#ifndef OPTOCOM_H
#define OPTOCOM_H

class OptoCom {
private:
    uint8_t rxPin;
    uint8_t txPin;
    uint32_t lastLow;
    uint32_t lastHigh;
    bool state;
    uint16_t delay;
public:
    OptoCom(uint8_t rxPin, uint8_t txPin);
    void loop();
    void write(uint16_t value);
    uint16_t read();
};

#endif