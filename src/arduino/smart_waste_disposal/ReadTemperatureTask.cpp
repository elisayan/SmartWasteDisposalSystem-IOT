#include "ReadTemperatureTask.h"
#include "MsgService.h"

#define MAX_TEMPERATURE 25.0

ReadTemperatureTask::ReadTemperatureTask(SmartWastePlant* pPlant, LCDDisplayI2C* lcd) {
  this->pPlant = pPlant;
  this->lcd = lcd;
  state = MEASURE;
  MsgService.init();
}

void ReadTemperatureTask::tick() {
  // Serial.print("Task State: ");
  // Serial.println(state);
  // Serial.print("System State: ");
  // Serial.println(pPlant->getStateName());
  
  if (pPlant->isIdle() && state == MEASURE) {
    return;
  }

  switch (state) {
    // case INIT:

    //   break;

    case MEASURE:
      //if (!pPlant->isIdle()) {
      Serial.print("temperature: ");
      Serial.println(pPlant->getCurrentTemperature());
      if (pPlant->getCurrentTemperature() >= MAX_TEMPERATURE) {
        pPlant->waitForOperatorRestore();
        state = ALARM;
      }
      //}
      break;

    case ALARM:
      if (pPlant->isReadyForRestore()) {
        Serial.println("ALARM");
        pPlant->alarmOn();
        lcd->problemDetected();
        if (MsgService.isMsgAvailable() && MsgService.receiveMsg()->getContent() == "Maintenance done!") {
          state = DONE;
        }
        // if (pPlant->getCurrentTemperature() < MAX_TEMPERATURE) {
        //   state = DONE;
        // }
      }
      break;

    case DONE:
      Serial.println("READY");
      pPlant->setIdle();
      Serial.println(pPlant->getStateName());
      state = MEASURE;
      break;
  }
}
