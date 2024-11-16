#include "Arduino.h"
#include "ReceivingWasteTask.h"

ReceivingWasteTask::ReceivingWasteTask(ServoMotor* motor, LCDDisplayI2C* lcd, ButtonImpl* button2) {
  this->motor = motor;
  this->lcd = lcd;
  this->button2 = button2;
}

void ReceivingWasteTask::init(int period) {
  Task::init(period);
}

void ReceivingWasteTask::tick() {
}
