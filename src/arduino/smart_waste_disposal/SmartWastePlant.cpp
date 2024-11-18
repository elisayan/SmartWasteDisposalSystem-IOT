#include <EnableInterrupt.h>
#include <avr/sleep.h>
#include "SmartWastePlant.h"
#include "Config.h"

SmartWastePlant::SmartWastePlant() {
  enableInterrupt(MOTOR, wakeUp, RISING);
  enableInterrupt(BUTTON1, wakeUp, RISING);
  enableInterrupt(BUTTON2, wakeUp, RISING);
  enableInterrupt(PIR, wakeUp, RISING);
  enableInterrupt(SONAR_ECHO, wakeUp, RISING);
  enableInterrupt(SONAR_TRIG, wakeUp, RISING);
  enableInterrupt(LM35, wakeUp, RISING);
}

void SmartWastePlant::init() {
  pMotor = new ServoMotor(MOTOR);
  pLcd = new LCDDisplayI2C();
  pOpenButton = new ButtonImpl(BUTTON1);
  pCloseButton = new ButtonImpl(BUTTON2);
  pLed1 = new Led(LED1);
  pLed2 = new Led(LED2);
  pPir = new Pir(PIR);
  pSonar = new Sonar(SONAR_ECHO, SONAR_TRIG);
  pTemp = new TempSensorLM35(LM35);

  Serial.println("Calibrating pir sensor...");
  pPir->calibrate();

  state = IDLE;
}

void SmartWastePlant::wakeUp() {
}

void SmartWastePlant::openDoor() {
  pMotor->on();
  pMotor->setPosition(90);
}

void SmartWastePlant::closeDoor() {
  pMotor->setPosition(0);
}

void SmartWastePlant::setAvailable() {
  pLed1->switchOn();
}

void SmartWastePlant::alarmOn() {
  pLed2->switchOn();
}

void SmartWastePlant::setIdle() {
  state = IDLE;
}

bool SmartWastePlant::isIdle() {
  return state == IDLE;
}

void SmartWastePlant::prepareToSleep() {
  if (pLed2->isOn()) {
    pLed1->switchOff();
  } else {
    pLed1->switchOn();
  }
  Serial.println("The system will enter in sleep mode in 3 second...");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  delay(1000);
  Serial.flush();

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
}

void SmartWastePlant::resumeFromSleeping() {
  sleep_disable();
  Serial.println("The system has woken up from sleep mode.");
}

void SmartWastePlant::readyForReceiveWaste() {
  state = READY_FOR_RECEIVE_WASTE;
}

bool SmartWastePlant::isReadyForReceiveWaste() {
  return state == READY_FOR_RECEIVE_WASTE;
}

bool SmartWastePlant::isReceivingWaste() {
  return state == RECEIVING_WASTE;
}

void SmartWastePlant::receivingWaste() {
  state = RECEIVING_WASTE;
}

void SmartWastePlant::wasteReceived() {
  state = WASTE_RECEIVED;
}

void SmartWastePlant::readyForEmpty() {
  state = READY_FOR_EMPTY;
}

bool SmartWastePlant::isReadyForEmpty() {
  return state == READY_FOR_EMPTY;
}

bool SmartWastePlant::isEmptying() {
  return state == EMPTYING;
}

void SmartWastePlant::emptying() {
  state = EMPTYING;
}

void SmartWastePlant::emptied() {
  state = EMPTIED;
}

void SmartWastePlant::setInMaintenance() {
  state = MAINTENANCE;
}

bool SmartWastePlant::isInMaintenance() {
  return state == MAINTENANCE;
} 

void SmartWastePlant::maintenanceDone() {
  state = READY_FOR_RESTORE;
}

bool SmartWastePlant::isReadyForRestore() {
  return state == READY_FOR_RESTORE;
}

double SmartWastePlant::getCurrentWasteDistance() {
  return pSonar->getDistance();
}

bool SmartWastePlant::detectedUserPresence() {
  return pPir->isDetected();
}

double SmartWastePlant::getCurrentTemperature() {
  return pTemp->getTemperature();
}
