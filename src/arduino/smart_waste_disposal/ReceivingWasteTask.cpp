#include "Arduino.h"
#include "ReceivingWasteTask.h"

#define TIME1 10000
#define TIME2 5000
#define DISTANCE1 0.05

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
          state = INIT;
        }
      }
      break;

    case CLOSED:
      if (pPlant->isWasteReceived()) {
        if (isFull()) {
          pPlant->readyForEmpty();
        } else {
          pPlant->setIdle();
        }
        state = INIT;
      }
      break;
  }
}

bool ReceivingWasteTask::isFull() {
  return pPlant->getCurrentWasteDistance() <= DISTANCE1;
}

