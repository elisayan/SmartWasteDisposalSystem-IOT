/*
 * Assignment #2 - Smart Waste Disposal System
 * Author: Elisa Yan
 */

#include "Config.h"
#include "SmartWastePlant.h"
#include "LCDDisplayI2C.h"
#include "Scheduler.h"
#include "MsgService.h"
#include "ReadyTask.h"
#include "ReceivingWasteTask.h"
#include "EmptyTask.h"
#include "ReadTemperatureTask.h"

Scheduler sched;
SmartWastePlant* pSmartWastePlant;
LCDDisplayI2C* lcd;

void setup() {
  Serial.begin(115200);
  lcd = new LCDDisplayI2C();

  sched.init(100);
  MsgService.init();
  pSmartWastePlant = new SmartWastePlant();
  pSmartWastePlant->init();

  Task* ready = new ReadyTask(pSmartWastePlant, lcd);
  ready->init(100);
  sched.addTask(ready);

  Task* receive = new ReceivingWasteTask(pSmartWastePlant, lcd);
  receive->init(200);
  sched.addTask(receive);

  Task* empty = new EmptyTask(pSmartWastePlant, lcd);
  empty->init(100);
  sched.addTask(empty);

  Task* temperature = new ReadTemperatureTask(pSmartWastePlant, lcd);
  temperature->init(200);
  sched.addTask(temperature);
}

void loop() {
  // Serial.print("temperature: ");
  // Serial.println(pSmartWastePlant->getCurrentTemperature());
  //Serial.println(pSmartWastePlant->getCurrentTemperature());
  //Serial.println(pSmartWastePlant->getCurrentWasteDistance());
  //Serial.println(pSmartWastePlant->detectedUserPresence());
  sched.schedule();
}