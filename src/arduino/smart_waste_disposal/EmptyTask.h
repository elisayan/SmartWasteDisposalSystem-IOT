#ifndef __EMPTY_TASK__
#define __EMPTY_TASK__

#include "Task.h"
#include "SmartWastePlant.h"
#include "LCDDisplayI2C.h"

class EmptyTask : public Task {
public:
  EmptyTask(SmartWastePlant* pPlant, LCDDisplayI2C* lcd);
  void tick();

private:
  enum { EMPTYING,
         MAINTENANCE } state;

  SmartWastePlant* pPlant;
  LCDDisplayI2C* lcd;
};

#endif