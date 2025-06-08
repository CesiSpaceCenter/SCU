#include "optocom.h"

OptoCom::OptoCom(uint8_t rxPin, uint8_t txPin) {
    this->rxPin = rxPin;
    this->txPin = txPin;

    pinMode(this->rxPin, INPUT);
    pinMode(this->txPin, OUTPUT);
}

void OptoCom::write(uint16_t value) {
    this->delay = value;
}

uint16_t OptoCom::read() {
    pulseIn(this->rxPin, LOW, 100000);
    return pulseIn(this->rxPin, HIGH, 100000)/1000;
}

void OptoCom::loop() {
    if (this->state && millis() - this->lastLow > this->delay) {
        digitalWrite(this->txPin, LOW);
        this->state = false;
        this->lastLow = millis();
    } else if (!this->state && millis() - this->lastHigh > this->delay) {
        digitalWrite(this->txPin, HIGH);
        this->state = true;
        this->lastHigh = millis();
    }
}