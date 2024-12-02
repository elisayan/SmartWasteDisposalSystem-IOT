#include <EnableInterrupt.h>
#include <avr/sleep.h>
#include "SmartWastePlant.h"
#include "Config.h"

void wakeUp() {
}

SmartWastePlant::SmartWastePlant() {
  enableInterrupt(MOTOR, wakeUp, RISING);
  enableInterrupt(BUTTON1, wakeUp, RISING);
  enableInterrupt(BUTTON2, wakeUp, RISING);
  enableInterrupt(PIR, wakeUp, RISING);
  enableInterrupt(SONAR_ECHO, wakeUp, RISING);
  enableInterrupt(SONAR_TRIG, wakeUp, RISING);
  enableInterrupt(TMP36, wakeUp, RISING);
}

void SmartWastePlant::init() {
  pMotor = new ServoMotor(MOTOR);
  pOpenButton = new ButtonImpl(BUTTON1);
  pCloseButton = new ButtonImpl(BUTTON2);
  pLed1 = new Led(LED1);
  pLed2 = new Led(LED2);
  pPir = new Pir(PIR);
  pSonar = new Sonar(SONAR_ECHO, SONAR_TRIG);
  pTemp = new TempSensorTMP36(TMP36);

  Serial.println("Calibrating pir sensor...");
  pPir->calibrate();
  delay(2000);
  Serial.println("Done!");

  state = IDLE;
}

void SmartWastePlant::openDoor() {
  pMotor->on();
  pMotor->setPosition(90);
}

void SmartWastePlant::closeDoor() {
  pMotor->on();
  pMotor->setPosition(0);
}

void SmartWastePlant::emptyWaste() {
  pMotor->on();
  pMotor->setPosition(-90);
  pMotor->off();
}

void SmartWastePlant::setAvailable() {
  pLed1->switchOn();
  pLed2->switchOff();
}

void SmartWastePlant::alarmOn() {
  pLed1->switchOff();
  pLed2->switchOn();
}

void SmartWastePlant::setIdle() {
  state = IDLE;
}

bool SmartWastePlant::isIdle() {
  return state == IDLE;
}

void SmartWastePlant::prepareToSleep() {
  Serial.println("The system will enter in sleep mode in 3 second...");
  Serial.println("3");
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

bool SmartWastePlant::isWasteReceived() {
  return state == WASTE_RECEIVED;
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

void SmartWastePlant::waitForOperatorRestore() {
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

bool SmartWastePlant::isDoorOpened() {
  return pOpenButton->isPressed();
}

bool SmartWastePlant::isDoorClosed() {
  return pCloseButton->isPressed();
}

int SmartWastePlant::getState() {
    return state;
}

const char* SmartWastePlant::getStateName() {
    switch (state) {
        case IDLE:
            return "IDLE";
        case READY_FOR_RECEIVE_WASTE:
            return "READY_FOR_RECEIVE_WASTE";
        case RECEIVING_WASTE:
            return "RECEIVING_WASTE";
        case WASTE_RECEIVED:
            return "WASTE_RECEIVED";
        case READY_FOR_EMPTY:
            return "READY_FOR_EMPTY";
        case EMPTYING:
            return "EMPTYING";
        case EMPTIED:
            return "EMPTIED";
        case READY_FOR_RESTORE:
            return "READY_FOR_RESTORE";
        default:
            return "UNKNOWN";
    }
}
