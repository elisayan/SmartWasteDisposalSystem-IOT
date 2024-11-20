#ifndef __READYTASK__
#define __READYTASK__

#include "Task.h"
#include "LCDDisplayI2C.h"
#include "SmartWastePlant.h"

class ReadyTask : public Task {
public:
  ReadyTask(SmartWastePlant* pPlant, LCDDisplayI2C* lcd);
  void tick();

private:
  bool isSleepTimeOut();

  enum { INIT,
         SLEEP,
         WAITING } state;

  unsigned long startTime = 0.0;

  LCDDisplayI2C* lcd;
  SmartWastePlant* pPlant;
};

#endif
