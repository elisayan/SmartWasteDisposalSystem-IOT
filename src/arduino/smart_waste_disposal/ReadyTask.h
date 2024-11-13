#ifndef __READYTASK__
#define __READYTASK__

#include "Task.h"
#include "Light.h"

class ReadyTask : public Task {
  int pin;
  Light* led;
  enum { ON,
         OFF } state;

public:
  ReadyTask(int pinLed1, int pinMotor);
  void init(int period);
  void tick();
}

#endif
