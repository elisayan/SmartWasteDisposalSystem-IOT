#include "ReadTemperatureTask.h"
#include "MsgService.h"

ReadTemperatureTask::ReadTemperatureTask(SmartWastePlant* pPlant, LCDDisplayI2C* lcd) {
  this->pPlant = pPlant;
  this->lcd = lcd;
  MsgService.init();
}

void ReadTemperatureTask::tick() {
  switch (state) {
    case MEASURE:
    
      break;

    case EXCEEDS:
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