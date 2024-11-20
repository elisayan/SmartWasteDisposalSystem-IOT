#ifndef __RECEIVING_WASTE_TASK__
#define __RECEIVING_WASTE_TASK__

#include "Task.h"
#include "SmartWastePlant.h"
#include "LCDDisplayI2C.h"

class ReceivingWasteTask : public Task {
public:
  ReceivingWasteTask(SmartWastePlant* pPlant, LCDDisplayI2C* lcd);
  void tick();

private:
  bool isFull();
  void prepareToBeEmptied();
  bool isTemperatureExceed();

  enum { SPILLING,
         CLOSED,
         FULL,
         ALARM } state;

  unsigned long timeSpilling = 0.0;

  SmartWastePlant* pPlant;
  LCDDisplayI2C* lcd;
};

#endif
