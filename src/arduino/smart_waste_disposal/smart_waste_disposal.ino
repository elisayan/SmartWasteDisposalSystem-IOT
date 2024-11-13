/*
 * Assignment #2 - Smart Waste Disposal System
 * Author: Elisa Yan
 */

#include "Config.h"
#include "ServoMotorImpl.h"
#include "LCDDisplayI2C.h"
#include "ButtonImpl.h"
#include "Led.h"
#include "Pir.h"
#include "Sonar.h"
#include "TempSensorLM35.h"
#include "Scheduler.h"
#include "ReadyTask.h"

Scheduler sched;

ServoMotor* motor;
LCDDisplayI2C* lcd;
ButtonImpl* button1;
ButtonImpl* button2;
Led* led1;
Led* led2;
Pir* pir;
Sonar* sonar;
TempSensorLM35* temp;

void setup() {
  Serial.begin(9600);
  sched.init(50);

  Task* ready = new ReadyTask(LED1, MOTOR);
  ready->init(500);
  sched.addTask(ready);
}

void loop() {
  sched.schedule();
}
