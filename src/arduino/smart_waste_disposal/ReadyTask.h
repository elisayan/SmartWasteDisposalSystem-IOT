#ifndef __READYTASK__
#define __READYTASK__

#include "Task.h"
#include "Led.h"
#include "LCDDisplayI2C.h"
#include "ServoMotor.h"
#include "ButtonImpl.h"
#include "Pir.h"
#include "Sonar.h"
#include "TempSensorLM35.h"

#define TIME_SLEEP 5000  // Timeout for USER_DETECTED (5 seconds)

class ReadyTask : public Task {
  Led* led1;
  Led* led2;
  LCDDisplayI2C* lcd;
  ServoMotor* motor;
  ButtonImpl* button1;
  ButtonImpl* button2;
  Pir* pir;
  Sonar* sonar;
  TempSensorLM35* temp;

  unsigned long startTime = 0.0;

  enum { INIT,
         SLEEP,
         WAITING } state;

public:
  ReadyTask(Led* led1, Led* led2, ServoMotor* motor, LCDDisplayI2C* lcd, ButtonImpl* button1, ButtonImpl* button2, Pir* pir, Sonar* sonar, TempSensorLM35* temp);
  void init(int period);
  void tick();

private:
  bool isSleepTimeOut();
};

#endif
