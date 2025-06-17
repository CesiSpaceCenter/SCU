#include <Arduino.h>
#include <Servo.h>
#include "config.h"
#include "states.h"
#include "hardware/buzzer.h"
#include "hardware/optocom.h"
#include "hardware/led.h"
#include "hardware/switch.h"

SCUState state = STATE_STANDBY;

OptoCom* dcu;
Buzzer* buzzer;
Switch* jack;
Switch* servoSwitch;
Switch* armSwitch;
Servo* servo;

uint32_t apogeeTimer;
uint32_t landedTimer;

void setup() {
  Serial.begin(9600);
  dcu = new OptoCom(PIN_OPTOCOM_RX, PIN_OPTOCOM_TX);
  buzzer = new Buzzer(PIN_BUZZER);
  jack = new Switch(PIN_JACK);
  servoSwitch = new Switch(PIN_SW_SERVO);
  armSwitch = new Switch(PIN_SW_ARM);
  servo = new Servo();

  servo->attach(PIN_SERVO);
  buzzer->enabled = true;
}

void loop() {
  buzzer->loop();

  switch (state)
  {
  case STATE_STANDBY:
    // 150ms beep every 5s
    buzzer->offTime = 5000;
    buzzer->onTime = 150;

    if (servoSwitch->getState()) {  // open/close servo
      servo->write(SERVO_OPEN_ANGLE);
    } else {
      servo->write(SERVO_CLOSE_ANGLE);
    }

    if (armSwitch->getState()) {  // we want to switch to armed state
      if (!jack->getState(0)) {  // but the jack is not plugged in
        // beep continously
        buzzer->offTime = 0;
        buzzer->onTime = 10000;
      } else {
        state = STATE_ARMED;
        servo->write(SERVO_CLOSE_ANGLE);
      }
    }
    break;
  
  case STATE_ARMED:
    // 150ms beep every 1.5s
    buzzer->offTime = 1500;
    buzzer->onTime = 150;

    if (!armSwitch->getState()) {  // abort launch, go back to standby
      state = STATE_STANDBY;
    }

    if (!jack->getState()) {  // liftoff!
      apogeeTimer = millis();  // start the apogee timer
      state = STATE_ASCENT;
    }
    break;

  case STATE_ASCENT:
    // 1s beep every 2s
    buzzer->offTime = 2000;
    buzzer->onTime = 1000;

    if (millis() - apogeeTimer >= APOGEE_TIME) {  // apogee reached (timer)
      servo->write(SERVO_OPEN_ANGLE);  // open the servo
      landedTimer = millis();  // start the landed timer
      state = STATE_DESCENT;
    }
    break;

  case STATE_DESCENT:
    // 3*150ms beep every seconds
    buzzer->offTime = 250;
    buzzer->onTime = 150;

    if (millis() - landedTimer >= LANDED_TIME) {  // landed
      state = STATE_LANDED;
    }
    break;

  case STATE_LANDED:
    // 1s beep every 150ms
    buzzer->offTime = 150;
    buzzer->onTime = 1000;

  default:
    break;
  }
}
