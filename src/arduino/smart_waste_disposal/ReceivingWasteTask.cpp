#include "Arduino.h"
#include "ReceivingWasteTask.h"

#define TIME1 10000
#define TIME2 5000
#define DISTANCE1 5.0
#define MAX_TEMPERATURE 26

ReceivingWasteTask::ReceivingWasteTask(SmartWastePlant* pPlant, LCDDisplayI2C* lcd) {
  this->pPlant = pPlant;
  this->lcd = lcd;
  state = SPILLING;
}

void ReceivingWasteTask::tick() {
  switch (state) {
    case SPILLING:
      if (pPlant->isReadyForReceiveWaste()) {
        timeSpilling = millis();
        lcd->pressClose();
        pPlant->receivingWaste();
      }

      if (pPlant->isReceivingWaste()) {
        if (pPlant->isDoorClosed() || millis() - timeSpilling >= TIME2) {
          Serial.println("Close button clicked");
          pPlant->wasteReceived();
          pPlant->closeDoor();
          lcd->wasteReceived();
          delay(TIME2);
          pPlant->readyForReceiveWaste();
          state = CLOSED;
        }
      }

      // if (isFull()) {
      //   prepareToBeEmptied();
      //   pPlant->closeDoor();
      //   state = FULL;
      // }

      if (isTemperatureExceed()) {
        pPlant->alarmOn();
        pPlant->waitForOperatorRestore();
        lcd->problemDetected();
        state = ALARM;
      }
      break;

    case CLOSED:
      if (pPlant->isWasteReceived()) {
        if (isFull()) {
          prepareToBeEmptied();
          state = FULL;
        } else {
          pPlant->readyForReceiveWaste();
          state = SPILLING;
        }
      }
      break;

    case FULL:
      //TODO waiting operator for empty the container
      pPlant->isReadyForEmpty();
      break;

    case ALARM:
      if (pPlant->isReadyForRestore()) {

      }
      break;
  }
}

bool ReceivingWasteTask::isFull() {
  return pPlant->getCurrentWasteDistance() <= DISTANCE1;
}

void ReceivingWasteTask::prepareToBeEmptied() {
  pPlant->readyForEmpty();
  pPlant->alarmOn();
  lcd->containerFull();
}

bool ReceivingWasteTask::isTemperatureExceed() {
  return pPlant->getCurrentTemperature() >= MAX_TEMPERATURE;
}
