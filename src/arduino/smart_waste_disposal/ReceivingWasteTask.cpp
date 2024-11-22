#include "Arduino.h"
#include "ReceivingWasteTask.h"

#define TIME1 10000
#define TIME2 5000
#define DISTANCE1 1.0
#define MAX_TEMPERATURE 100

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

        if (isFull()) {
          pPlant->closeDoor();
          state = FULL;
        }
      }

      if (isTemperatureExceed()) {
        pPlant->waitForOperatorRestore();
        state = ALARM;
      }
      break;

    case CLOSED:
      if (pPlant->isWasteReceived()) {
        if (isFull()) {
          state = FULL;
        } else {
          pPlant->readyForReceiveWaste();
          state = SPILLING;
        }
      }
      break;

    case FULL:
      //TODO waiting operator for empty the container
      prepareToBeEmptied();
      pPlant->isReadyForEmpty();
      break;

    case ALARM:
      pPlant->alarmOn();
      lcd->problemDetected();
      if (pPlant->isReadyForRestore()) {
        Serial.println("Ready for operatore to restore the system...");
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
