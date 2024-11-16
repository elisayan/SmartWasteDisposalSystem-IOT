#include "Arduino.h"
#include "UserDetectionTask.h"

UserDetectionTask::UserDetectionTask(int pirPin) {
  this->pirPin = pirPin;
}

void UserDetectionTask::init(int period) {
  Task::init(period);
  pir = new Pir(pirPin);
  pir->calibrate();
}

void UserDetectionTask::tick() {
  pir->sync();
  Serial.println("testing");
  if (pir->isDetected()) {
    Serial.println("detected");
    // Puoi aggiungere logica aggiuntiva per svegliare il sistema
  } else{
    Serial.println("not");
  }
}
