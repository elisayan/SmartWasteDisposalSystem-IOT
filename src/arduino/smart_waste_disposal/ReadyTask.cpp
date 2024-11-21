#include "ReadyTask.h"
#include <Arduino.h>

#define TIME_SLEEP 30000

ReadyTask::ReadyTask(SmartWastePlant* pPlant, LCDDisplayI2C* lcd) {
  this->pPlant = pPlant;
  this->lcd = lcd;
  pPlant->setIdle();
  //Serial.println("ready task init");
  state = INIT;
}

void ReadyTask::tick() {
  switch (state) {
    case INIT:
      //Serial.println("tick init");
      if (pPlant->isIdle()) {
        startTime = millis();
        pPlant->setAvailable();
        pPlant->closeDoor();
        lcd->enterWaste();
        if (pPlant->isDoorOpened()) {
          Serial.println("button open clicked");
        }
        state = WAITING;
      }
      break;

    case SLEEP:
      if (pPlant->detectedUserPresence()) {
        Serial.println("User detected, waking up...");
        lcd->turnOn();
        lcd->enterWaste();
        pPlant->resumeFromSleeping();
        startTime = millis();
        state = WAITING;
      }
      break;

    case WAITING:
      if (isSleepTimeOut()) {
        Serial.println("SLEEPED");
        lcd->turnOff();
        pPlant->prepareToSleep();
        state = SLEEP;
      }

      if (pPlant->isDoorOpened()) {
        //TODO prossimo task
        Serial.println("button clicked");
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
