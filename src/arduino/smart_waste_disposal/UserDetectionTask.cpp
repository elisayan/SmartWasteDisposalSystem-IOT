#include "UserDetectionTask.h"

UserDetectionTask::UserDetectionTask(int pirPin) {
  this->pirPin = pirPin;
}

void UserDetectionTask::init(int period){
  Task::init(period);
  pir = new Pir(pirPin);
  pir->calibrate();
}

void UserDetectionTask::tick(){
  if(pir->isDetected()){
    //sveglia il sistema
  }
}
