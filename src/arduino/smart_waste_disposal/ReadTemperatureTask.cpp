#include "ReadTemperatureTask.h"
#include "MsgService.h"

#define MAX_TEMPERATURE 30
#define MAX_TEMP_TIME 5000

ReadTemperatureTask::ReadTemperatureTask(SmartWastePlant* pPlant, LCDDisplayI2C* lcd) {
  this->pPlant = pPlant;
  this->lcd = lcd;
  state = MEASURE;
  simTemp = 32; //to remove
  startOverheatTime = 0;
  MsgService.init();
}

void ReadTemperatureTask::tick() {
  unsigned long currentMillis = millis();
  
  Serial.print("temperature: ");
  Serial.println(pPlant->getCurrentTemperature());

  switch (state) {
    case MEASURE:
      //if (pPlant->getCurrentTemperature() >= MAX_TEMPERATURE) {
      if (simTemp >= MAX_TEMPERATURE) {
        if (startOverheatTime == 0) {
          startOverheatTime = currentMillis;
        } else if (currentMillis - startOverheatTime >= MAX_TEMP_TIME) {
          pPlant->waitForOperatorRestore();
          state = ALARM;
        }
      } else {
        startOverheatTime = 0;
      }
      break;

    case ALARM:
      if (pPlant->isReadyForRestore()) {
        Serial.println("ALARM");
        pPlant->alarmOn();
        lcd->problemDetected();
        if (MsgService.isMsgAvailable() && MsgService.receiveMsg()->getContent() == "DONE") {
          state = DONE;
          simTemp = 25;
        }
      }
      break;

    case DONE:
      Serial.println("READY");
      pPlant->setIdle();
      state = MEASURE;
      startOverheatTime = 0;
      break;
  }
}
