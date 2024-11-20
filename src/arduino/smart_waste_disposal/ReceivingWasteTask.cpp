#include "Arduino.h"
#include "ReceivingWasteTask.h"

#define TIME2 8000
#define DISTANCE1 5.0

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
        if (pPlant->isDoorClosed() || millis() - timeSpilling >= TIME2) {
          pPlant->wasteReceived();
          pPlant->closeDoor();
          lcd->wasteReceived();
          delay(TIME2);
          pPlant->readyForReceiveWaste();
          state = CLOSED;
        }

        // if (isFull()) {
        //   prepareToBeEmptied();
        //   pPlant->closeDoor();
        //   state = FULL;
        // }
      }
      break;

    case CLOSED:
      if (isFull()) {
        prepareToBeEmptied();
        state = FULL;
      } else {
        pPlant->readyForReceiveWaste();
        state = SPILLING;
      }
      break;

    case FULL:
      //TODO waiting operator for empty the container
      pPlant->isReadyForEmpty();
      break;

    case ALARM:
      break;
  }
}

bool ReceivingWasteTask::isFull() {
  return pPlant->getCurrentWasteDistance() <= DISTANCE1;
}

bool ReceivingWasteTask::prepareToBeEmptied() {
  pPlant->setInMaintenance();
  pPlant->alarmOn();
  lcd->containerFull();
  pPlant->alarmOn();
}
