#include "Arduino.h"
#include "ReceivingWasteTask.h"

#define TIME1 10000
#define TIME2 5000
#define DISTANCE1 0.05
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
        if (pPlant->isDoorClosed() || millis() - timeSpilling >= TIME1) {
          if (pPlant->isDoorClosed()) {
            Serial.println("Close button clicked");
          }
          pPlant->wasteReceived();
          pPlant->closeDoor();
          lcd->wasteReceived();
          delay(TIME2);
          state = CLOSED;
        }

        if (isFull()) {
          pPlant->closeDoor();
          fullTask();
        }
      }
      break;

    case CLOSED:
      Serial.println("Door closed");
      if (pPlant->isWasteReceived()) {
        fullTask();
      }
      break;

    case FULL:
      //TODO waiting operator for empty the container
      prepareToBeEmptied();
      pPlant->readyForEmpty();
      break;

    case ALARM:
      pPlant->alarmOn();
      lcd->problemDetected();
      if (pPlant->isReadyForRestore()) {
        Serial.println("Ready for operatore to restore the system...");
      }
      break;
  }
  Serial.println("check temperature");
  if (isTemperatureExceed()) {
    pPlant->waitForOperatorRestore();
    state = ALARM;
  }
}

bool ReceivingWasteTask::isFull() {
  return pPlant->getCurrentWasteDistance() <= DISTANCE1;
}

void ReceivingWasteTask::fullTask() {
  if (isFull()) {
    state = FULL;
  } else {
    Serial.println("Back to receive waste");
    pPlant->setIdle();
    state = INIT;
  }
}

void ReceivingWasteTask::prepareToBeEmptied() {
  pPlant->readyForEmpty();
  pPlant->alarmOn();
  lcd->containerFull();
}

bool ReceivingWasteTask::isTemperatureExceed() {
  return pPlant->getCurrentTemperature() >= MAX_TEMPERATURE;
}
