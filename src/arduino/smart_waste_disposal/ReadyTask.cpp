#include "ReadyTask.h"
#include <Arduino.h>

#define TIME_SLEEP 30000

ReadyTask::ReadyTask(SmartWastePlant* pPlant, LCDDisplayI2C* lcd) {
  this->pPlant = pPlant;
  this->lcd = lcd;
  lcd->welcome();
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
        Serial.print("distance: ");
        Serial.println(pPlant->getCurrentWasteDistance());
        state = WAITING;
      }
      break;

    case SLEEP:
      if (pPlant->detectedUserPresence()) {
        Serial.println("AWAKE");
        lcd->turnOn();
        lcd->enterWaste();
        pPlant->resumeFromSleeping();
        startTime = millis();
        state = WAITING;
      } else {
        Serial.println("SLEEP");
      }
      break;

    case WAITING:
      if (isSleepTimeOut()) {
        lcd->turnOff();
        pPlant->prepareToSleep();
        state = SLEEP;
      }

      if (pPlant->isDoorOpened()) {
        //Serial.println("OPEN");
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
