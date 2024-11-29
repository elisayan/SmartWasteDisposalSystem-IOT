#include "Arduino.h"
#include "ReceivingWasteTask.h"

#define TIME1 10000
#define TIME2 5000
#define DISTANCE1 0.02
#define MAX_TEMPERATURE 100

ReceivingWasteTask::ReceivingWasteTask(SmartWastePlant* pPlant, LCDDisplayI2C* lcd) {
  this->pPlant = pPlant;
  this->lcd = lcd;
  state = INIT;
}

void ReceivingWasteTask::tick() {
  switch (state) {
    case INIT:
      if (pPlant->isReadyForReceiveWaste()) {
        timeSpilling = millis();
        lcd->pressClose();
        pPlant->receivingWaste();
        state = SPILLING;
      }
      break;

    case SPILLING:
      if (pPlant->isReceivingWaste()) {
        Serial.println("SPILLING");
        Serial.print("distance: ");
        Serial.println(pPlant->getCurrentWasteDistance());
        if (pPlant->isDoorClosed() || millis() - timeSpilling >= TIME1) {
          pPlant->wasteReceived();
          pPlant->closeDoor();
          lcd->wasteReceived();
          delay(TIME2);
          state = CLOSED;
        }

        if (isFull()) {
          pPlant->closeDoor();
          pPlant->readyForEmpty();
          state = FULL;
        }
      }
      break;

    case CLOSED:
      if (pPlant->isWasteReceived()) {
        if (isFull()) {
          pPlant->readyForEmpty();
          state = FULL;
        } else {
          pPlant->setIdle();
          state = INIT;
        }
      }
      break;

    case FULL:
      if (pPlant->isReadyForEmpty()) {
        Serial.println("FULL");
        pPlant->alarmOn();
        lcd->containerFull();
        state = INIT;
      }
      break;

    case ALARM:
      if (pPlant->isReadyForRestore()) {
        Serial.println("ALARM");
        pPlant->alarmOn();
        lcd->problemDetected();
        state = INIT;
      }
      break;
  }

  // if (isTemperatureExceed()) {
  //   pPlant->waitForOperatorRestore();
  //   state = ALARM;
  // }
}

bool ReceivingWasteTask::isFull() {
  return pPlant->getCurrentWasteDistance() <= DISTANCE1;
}

bool ReceivingWasteTask::isTemperatureExceed() {
  return pPlant->getCurrentTemperature() >= MAX_TEMPERATURE;
}
