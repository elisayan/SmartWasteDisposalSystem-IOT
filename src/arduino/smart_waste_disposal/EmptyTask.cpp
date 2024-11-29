#include "EmptyTask.h"
#include "MsgService.h"

EmptyTask::EmptyTask(SmartWastePlant* pPlant, LCDDisplayI2C* lcd) {
  this->pPlant = pPlant;
  this->lcd = lcd;
  MsgService.init();
}

void EmptyTask::tick() {
  switch (state) {
    case EMPTYING:
      if (pPlant->isReadyForEmpty()) {
        pPlant->emptying();
        if (MsgService.isMsgAvailable()) {
          Msg* msg = MsgService.receiveMsg();
          if (msg->getContent() == "Maintenance done!") {
            pPlant->setIdle();
          }
        }
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