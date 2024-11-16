#ifndef __RECEIVING_WASTE_TASK__
#define __RECEIVING_WASTE_TASK__

#include "Task.h"
#include "ServoMotor.h"
#include "LCDDisplayI2C.h"
#include "ButtonImpl.h"

#define TIME2 8000  // Timeout for WAITING_FOR_WASTE (8 seconds)

class ReceivingWasteTask : public Task {
  ServoMotor* motor;
  LCDDisplayI2C* lcd;
  ButtonImpl* button2;

  enum { SPILLING,
         CLOSED,
         FULL } state;
public:
  ReceivingWasteTask(ServoMotor* motor, LCDDisplayI2C* lcd, ButtonImpl* button2);
  void init(int period);
  void tick();
};

#endif
