#include "EmptyTask.h"

EmptyTask::EmptyTask(SmartWastePlant* pPlant, LCDDisplayI2C* lcd) {
  this->pPlant = pPlant;
  this->lcd = lcd;
}

void EmptyTask::tick() {
  switch (state) {
    case EMPTYING:
      if (pPlant->isReadyForEmpty()) {
        Serial.println("EMPTYING");
        pPlant->emptying();
        //TODO if empty is done
        pPlant->setIdle();
      }
      break;

    case MAINTENANCE:
      if (pPlant->isReadyForRestore()) {
        Serial.println("RESTORING");
        //TODO check operator dashboard if restore is done
        pPlant->setIdle();
      }
      break;
  }
}