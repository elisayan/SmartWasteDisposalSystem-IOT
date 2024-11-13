/*
 * Assignment #2 - Smart Waste Disposal System
 * Author: Elisa Yan
 */

#include "Config.h"
#include "Servo_motor_impl.h"
#include "LCDDisplayI2C.h"
#include "ButtonImpl.h"
#include "Led.h"
#include "Pir.h"
#include "Sonar.h"
#include "TempSensorLM35.h"

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
  motor = new ServoMotorImpl(MOTOR);
  lcd = new LCDDisplayI2C();
  button1 = new ButtonImpl(BUTTON1);
  button2 = new ButtonImpl(BUTTON2);
  led1 = new Led(LED1);
  led2 = new Led(LED2);
  pir = new Pir(PIR);
  sonar = new Sonar(SONAR_ECHO, SONAR_TRIG);
  temp = new TempSensorLM35(LM35);
}

void loop() {
  lcd->setMessage("Ciao");
  delay(1000);
}
