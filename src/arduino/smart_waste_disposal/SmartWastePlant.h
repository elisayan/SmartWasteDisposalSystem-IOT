#ifndef __SMART_WASTE_PLANT__
#define __SMART_WASTE_PLANT__

#include <Arduino.h>
#include "ServoMotor.h"
#include "LCDDisplayI2C.h"
#include "ButtonImpl.h"
#include "Led.h"
#include "Pir.h"
#include "Sonar.h"
#include "TempSensorLM35.h"

class SmartWastePlant {
public:
  SmartWastePlant();
  void init();

  void openDoor();
  void closeDoor();
  void setAvailable();
  void alarmOn();

  void setIdle();
  bool isIdle();
  void prepareToSleep();
  void resumeFromSleeping();

  void readyForReceiveWaste();
  bool isReadyForReceiveWaste();
  bool isReceivingWaste();
  void receivingWaste();
  void wasteReceived();
  bool isWasteReceived();

  void readyForEmpty();
  bool isReadyForEmpty();
  bool isEmptying();
  void emptying();
  void emptied();

  void waitForOperatorRestore();
  bool isReadyForRestore();

  double getCurrentWasteDistance();
  bool detectedUserPresence();
  double getCurrentTemperature();
  bool isDoorOpened();
  bool isDoorClosed();

private:
  enum { IDLE,
         READY_FOR_RECEIVE_WASTE,
         RECEIVING_WASTE,
         WASTE_RECEIVED,
         READY_FOR_EMPTY,
         EMPTYING,
         EMPTIED,
         READY_FOR_RESTORE
  } state;

  ServoMotor* pMotor;
  LCDDisplayI2C* pLcd;
  ButtonImpl* pOpenButton;
  ButtonImpl* pCloseButton;
  Led* pLed1;
  Led* pLed2;
  Pir* pPir;
  Sonar* pSonar;
  TempSensorLM35* pTemp;
};

#endif