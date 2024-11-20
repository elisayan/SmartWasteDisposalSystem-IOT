#include "EmptyTask.h"

EmptyTask::EmptyTask(SmartWastePlant* pPlant, LCDDisplayI2C* lcd) {
  this->pPlant = pPlant;
  this->lcd = lcd;
}

void EmptyTask::tick() {
  switch (state) {
    case TEST:
      break;
  }
}