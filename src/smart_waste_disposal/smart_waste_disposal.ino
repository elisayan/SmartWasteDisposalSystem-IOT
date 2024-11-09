/*
 * Assignment #2 - Smart Waste Disposal System
 * Author: Elisa Yan
 */

#include "Servo_motor_impl.h"

ServoMotor* motor;

void setup() {
  Serial.begin(9600);
  motor = new ServoMotorImpl(9);
}

void loop() {
  motor->on();
  motor->setPosition(90);
  Serial.println("90");
  delay(1000);
  motor->setPosition(0);
  Serial.println("0");
  delay(1000);
  motor->setPosition(-90);
  Serial.println("-90");
  delay(1000);
  motor->off();
  delay(1000);
}
