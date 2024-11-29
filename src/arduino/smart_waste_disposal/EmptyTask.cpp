#include "EmptyTask.h"
#include "MsgService.h"

EmptyTask::EmptyTask(SmartWastePlant* pPlant, LCDDisplayI2C* lcd) {
  this->pPlant = pPlant;
  this->lcd = lcd;
  state = INIT;
}

void EmptyTask::tick() {
  switch (state) {
    case INIT:
      if (pPlant->isReadyForEmpty()) {
        Serial.println("FULL");
        pPlant->alarmOn();
        lcd->containerFull();
        pPlant->emptying();
        state = EMPTYING;
      }
      break;

    case EMPTYING:
      if (pPlant->isEmptying()) {
        if (MsgService.isMsgAvailable() && MsgService.receiveMsg()->getContent() == "Maintenance done!") {
          state = DONE;
          pPlant->emptied();
        }
      }
      break;

    case DONE:
      pPlant->setIdle();
      state = INIT;
      Serial.println("READY");
      break;
  }
}