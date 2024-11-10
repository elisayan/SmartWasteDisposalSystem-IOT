/*
 * Assignment #2 - Smart Waste Disposal System
 * Author: Elisa Yan
 */

#include "Servo_motor_impl.h"
#include "LCDDisplayI2C.h"

ServoMotor* motor;
LCDDisplayI2C* lcd;

void setup() {
  Serial.begin(9600);
  motor = new ServoMotorImpl(9);
  lcd = new LCDDisplayI2C();
}

void loop() {
  lcd->setMessage("Ciao");
  delay(1000);
}
