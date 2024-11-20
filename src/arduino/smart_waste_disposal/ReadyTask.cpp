#include "ReadyTask.h"
#include <Arduino.h>

#define TIME_SLEEP 5000

ReadyTask::ReadyTask(SmartWastePlant* pPlant, LCDDisplayI2C* lcd) {
  this->pPlant = pPlant;
  this->lcd = lcd;
  pPlant->setIdle();
  state = INIT;
}

void ReadyTask::tick() {
  switch (state) {
    case INIT:
      if (pPlant->isIdle()) {
        startTime = millis();
        pPlant->setAvailable();
        pPlant->closeDoor();
        lcd->enterWaste();
        state = WAITING;
      }
      break;

    case SLEEP:
      if (pPlant->detectedUserPresence()) {
        pPlant->resumeFromSleeping();
        startTime = millis();
        state = WAITING;
      }
      break;

    case WAITING:
      if (isSleepTimeOut()) {
        pPlant->prepareToSleep();
        state = SLEEP;
      }

      if (pPlant->isDoorOpened()) {
        //TODO prossimo task
        pPlant->openDoor();
        pPlant->readyForReceiveWaste();
        state = INIT;
      }
      break;
  }
}

bool ReadyTask::isSleepTimeOut() {
  return millis() - startTime >= TIME_SLEEP;
}
