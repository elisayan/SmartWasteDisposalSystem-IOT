#include "servo_motor_impl.h"
#include "Arduino.h"

ServoMotorImpl::ServoMotorImpl(int pin) {
  this->pin = pin;
}

void ServoMotorImpl::on() {
  motor.attach(pin);
}

void ServoMotorImpl::setPosition(int angle) {
  if (angle > 90) {
    angle = 90;
  } else if (angle < -90) {
    angle = -90;
  }
  
  float coeff = (2400.0 - 544.0) / 180.0;
  int pulseWidth = 544 + (angle + 90) * coeff;

  motor.write(pulseWidth);
}

void ServoMotorImpl::off() {
  motor.detach();
}
