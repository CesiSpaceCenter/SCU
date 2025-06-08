#include <Arduino.h>
#include "buzzer.h"


Buzzer::Buzzer(uint8_t pin) {
    this->pin = pin;
    pinMode(this->pin, OUTPUT);
    digitalWrite(this->pin, LOW);
}

void Buzzer::on() {
    digitalWrite(this->pin, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
}

void Buzzer::off() {
    digitalWrite(this->pin, LOW);
    digitalWrite(LED_BUILTIN, LOW);
}

void Buzzer::beep(uint16_t duration = 200, uint8_t repeat = 1) {
    if (this->enabled) {
        this->off();
        delay(100);
    }
    this->on();
    delay(duration);
    this->off();
    if (this->enabled) {
        delay(100);
    }
}

void Buzzer::loop() {
    if (!this->enabled && this->state) {
        this->off();
        this->state = true;
    } else if (this->state && millis() - this->lastOn > this->onTime) {
        this->off();
        this->state = false;
        this->lastOff = millis();
    } else if (!this->state && millis() - this->lastOff > this->offTime) {
        this->on();
        this->state = true;
        this->lastOn = millis();
    }
}