#include "ReadyTask.h"

ReadyTask::ReadyTask(Led* led1, ServoMotor* motor, LCDDisplayI2C* lcd) {
  this->led1 = led1;
  this->motor = motor;
  this->lcd = lcd;
}

void ReadyTask::init(int period) {
  Task::init(period);
  state = IDLE;
}

void ReadyTask::tick() {
  switch (state) {
    case IDLE:
      motor->on();
      led1->switchOn();
      motor->setPosition(0);
      lcd->enterWaste();
      //motor->off();
      break;

    case SLEEP:

      break;
  }
}
