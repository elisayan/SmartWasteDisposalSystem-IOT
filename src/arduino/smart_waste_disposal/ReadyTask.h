#ifndef __READYTASK__
#define __READYTASK__

#include "Task.h"
#include "Led.h"
#include "LCDDisplayI2C.h"
#include "ServoMotorImpl.h"

class ReadyTask : public Task {
  int pinLed1;
  int pinMotor;
  Light* led1;
  LCDDisplayI2C* lcd;
  ServoMotorImpl* motor;

public:
  ReadyTask(int pinLed1, int pinMotor);
  void init(int period);
  void tick();
};

#endif
