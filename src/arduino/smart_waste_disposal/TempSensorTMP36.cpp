#include "TempSensorTMP36.h"
#include <Arduino.h>

#define VCC ((float)5)

TempSensorTMP36::TempSensorTMP36(int p)
  : pin(p) {
}

float TempSensorTMP36::getTemperature() {
  int reading = analogRead(pin);
  float voltage = reading * (5.0 / 1024.0);
  float temperatureC = (voltage - 0.5) * 100;
  return temperatureC;
}
