/*
 * Assignment #2 - Smart Waste Disposal System
 * Author: Elisa Yan
 */

#include "Config.h"
#include "Scheduler.h"
#include "ReadyTask.h"

Scheduler sched;

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
