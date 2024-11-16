#include "ReadyTask.h"
#include <Arduino.h>
#include <avr/sleep.h>

ReadyTask::ReadyTask(Led* led1, Led* led2, ServoMotor* motor, LCDDisplayI2C* lcd, ButtonImpl* button1, ButtonImpl* button2, Pir* pir, Sonar* sonar, TempSensorLM35* temp) {
  this->led1 = led1;
  this->led2 = led2;
  this->motor = motor;
  this->lcd = lcd;
  this->button1 = button1;
  this->button2 = button2;
  this->pir = pir;
  this->sonar = sonar;
  this->temp = temp;
}

void ReadyTask::init(int period) {
  Task::init(period);
  state = INIT;
}

void ReadyTask::tick() {
  switch (state) {
    case INIT:
      startTime = millis();
      motor->on();
      led1->switchOn();
      motor->setPosition(0);
      lcd->enterWaste();
      //motor->off();
      state = WAITING;
      break;

    case SLEEP:
      if (pir->isDetected()) {
        sleep_disable();
        Serial.println("The game has woken up from sleep mode.");
        startTime = millis();
        state = WAITING;
      }
      break;

    case WAITING:
      if (isSleepTimeOut()) {
        Serial.println("The game will enter power-down mode in 1 second. Press any button to awoken.");
        delay(1000);
        Serial.flush();

        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        sleep_mode();
        state = SLEEP;
      }

      if(button1->isPressed()){
        Task::setActive(false);
        //TODO prossimo task
        state = INIT;
      }
      break;
  }
}

bool ReadyTask::isSleepTimeOut() {
  return millis() - startTime >= TIME_SLEEP;
}
