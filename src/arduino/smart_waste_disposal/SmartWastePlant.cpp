#include "SmartWastePlant.h"
#include "Config.h"

SmartWastePlant::SmartWastePlant() {
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

void SmartWastePlant::prepareToSleep() {
  if (pLed2->isOn()) {
    pLed1->switchOff();
  } else {
    pLed1->switchOn();
  }
  //TODO sleep code
}

void SmartWastePlant::resumeFromSleeping() {

}