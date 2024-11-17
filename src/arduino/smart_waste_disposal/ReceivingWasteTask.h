#ifndef __RECEIVING_WASTE_TASK__
#define __RECEIVING_WASTE_TASK__

#include "Task.h"
#include "ServoMotor.h"
#include "LCDDisplayI2C.h"
#include "ButtonImpl.h"
#include "Sonar.h"

#define TIME2 8000  // Timeout for WAITING_FOR_WASTE (8 seconds)
#define DISTANCE1 5.0

class ReceivingWasteTask : public Task {
  ServoMotor* motor;
  LCDDisplayI2C* lcd;
  ButtonImpl* button2;
  Sonar* sonar;

  unsigned long timeSpilling = 0.0;

  enum { SPILLING,
         CLOSED,
         FULL } state;
public:
  ReceivingWasteTask(ServoMotor* motor, LCDDisplayI2C* lcd, ButtonImpl* button2, Sonar* sonar);
  void init(int period);
  void tick();

private:
  void closeDoor();
  bool isFull();
};

#endif
