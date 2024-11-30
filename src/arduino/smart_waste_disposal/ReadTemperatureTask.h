#ifndef __READ_TEMPERATURE_TASK__
#define __READ_TEMPERATURE_TASK__

#include "Task.h"
#include "SmartWastePlant.h"
#include "LCDDisplayI2C.h"

class ReadTemperatureTask : public Task {
public:
  ReadTemperatureTask(SmartWastePlant* pPlant, LCDDisplayI2C* lcd);
  void tick();

private:
  enum { MEASURE,
         ALARM,
         DONE } state;

  SmartWastePlant* pPlant;
  LCDDisplayI2C* lcd;
  unsigned long startOverheatTime;
  float simTemp;
};

#endif