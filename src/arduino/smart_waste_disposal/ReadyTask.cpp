#include "ReadyTask.h"

ReadyTask::ReadyTask(int pinLed1, int pinMotor) {
  this->pinLed1 = pinLed1;
  this->pinMotor = pinMotor;
}

void ReadyTask::init(int period){
  Task::init(period);
  led1 = new Led(pinLed1);
  lcd = new LCDDisplayI2C();
  motor = new ServoMotorImpl(pinMotor);
}

void ReadyTask::tick(){
  led1->switchOn();
  motor->setPosition(0);
  lcd->setMessage("PRESS OPEN TO ENTER WASTE");
}
