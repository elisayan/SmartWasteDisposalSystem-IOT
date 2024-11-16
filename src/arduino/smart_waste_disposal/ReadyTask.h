#ifndef __READYTASK__
#define __READYTASK__

#include "Task.h"
#include "Led.h"
#include "LCDDisplayI2C.h"
#include "ServoMotor.h"

class ReadyTask : public Task {
  int pinLed1;
  int pinMotor;
  Led* led1;
  LCDDisplayI2C* lcd;
  ServoMotor* motor;
  enum { IDLE,
         SLEEP } state;

public:
  ReadyTask(Led* led1, ServoMotor* motor, LCDDisplayI2C* lcd);
  void init(int period);
  void tick();
};

#endif
