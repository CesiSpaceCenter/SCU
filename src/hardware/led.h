#include "Arduino.h"

#ifndef LED_H
#define LED_H

class LED
{
private:
    uint8_t pin;
    uint16_t blinkInterval = 0;
    uint32_t lastBlink = 0;
    bool blinkState = 0;
public:
    LED(uint8_t pin) {
        this->pin = pin;
        pinMode(this->pin, OUTPUT);
    };

    void on() {
        digitalWrite(this->pin, HIGH);
    };
    void off() {
        digitalWrite(this->pin, LOW);
        this->blinkInterval = 0;
    }
    void blink(uint16_t interval = 1000) {
        this->blinkInterval = interval;
    };

    void loop() {
        if (this->blinkInterval > 0 && (millis() - this->lastBlink) > this->blinkInterval) {
            digitalWrite(this->pin, !this->blinkState);
            this->lastBlink = millis();
            this->blinkState = !this->blinkState;
        }
    }
};

#endif