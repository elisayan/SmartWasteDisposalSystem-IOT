#ifndef __SMART_WASTE_PLANT__
#define __SMART_WASTE_PLANT__

#include <Arduino.h>
#include "Led.h"
#include "ButtonImpl.h"
#include "Sonar.h"
#include "Pir.h"
#include "TempSensor.h"
#include "ServoMotor.h"

class SmartWastePlant {
public:
  SmartWastePlant();
  void init();


private:
  enum { IDLE,
         READY_FOR_RECEIVE_WASTE,
         RECEIVING_WASTE,
         WASTE_RECEIVED,
         READY_FOR_EMPTY,
         EMPTYING,
         EMPTED,
         READY_FOR_RESTORE,
         MAINTENANCE
  }

  Led* pLed1;
  Led* pLed2;
  ButtonImpl* openButton;
  ButtonImpl* closeButton;
  Sonar* pSonar;
  Pir* pPir;
  TempSensor* pTempSensor;
  ServoMotor* pDoorMotor;
}

#endif