#include "Arduino.h"
#include "ReceivingWasteTask.h"

ReceivingWasteTask::ReceivingWasteTask(ServoMotor* motor, LCDDisplayI2C* lcd, ButtonImpl* button2, Sonar* sonar) {
  this->motor = motor;
  this->lcd = lcd;
  this->button2 = button2;
  this->sonar = sonar;
}

void ReceivingWasteTask::init(int period) {
  Task::init(period);
  motor->on();
  motor->setPosition(90);
  state = SPILLING;
}

void ReceivingWasteTask::tick() {
  switch (state) {
    case SPILLING:
      timeSpilling = millis();
      lcd->pressClose();
      if (button2->isPressed() || millis() - timeSpilling >= TIME2) {
        closeDoor();
        lcd->wasteReceived();
        delay(TIME2);
        state = CLOSED;
      }

      if (isFull()) {
        closeDoor();
        lcd->containerFull();
        //TODO l1 off, l2 on
        state = FULL;
      }
      break;

    case CLOSED:
      if (isFull()) {
        closeDoor();
        lcd->containerFull();
        state = FULL;
      } else {
        state = SPILLING;
      }
      break;

    case FULL:
      Task::setActive(false);
      //TODO waiting operator for empty the container
      break;
  }
}

void ReceivingWasteTask::closeDoor() {
  motor->on();
  motor->setPosition(0);
}

bool ReceivingWasteTask::isFull() {
  return sonar->getDistance() <= DISTANCE1;
}
