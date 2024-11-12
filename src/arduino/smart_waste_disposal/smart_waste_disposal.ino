/*
 * Assignment #2 - Smart Waste Disposal System
 * Author: Elisa Yan
 */

#include "Config.h"
#include "Servo_motor_impl.h"
#include "LCDDisplayI2C.h"
#include "ButtonImpl.h"

ServoMotor* motor;
LCDDisplayI2C* lcd;
ButtonImpl* button1;
ButtonImpl* button2;

void setup() {
  Serial.begin(9600);
  motor = new ServoMotorImpl(9);
  lcd = new LCDDisplayI2C();
  button1 = new Button(4);
  button2 = new Button(5);
}

void loop() {
  lcd->setMessage("Ciao");
  delay(1000);
}
