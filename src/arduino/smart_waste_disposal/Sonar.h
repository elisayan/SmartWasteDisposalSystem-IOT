#ifndef __SONAR__
#define __SONAR__

#include "ProximitySensor.h"

#define NO_OBJ_DETECTED -1

class Sonar : public ProximitySensor {

public:
  Sonar(int echoPin, int trigPin);
  float getDistance();
  void setTemperature(float temp);

private:
  float getSoundSpeed();

  float temperature;
  int echoPin, trigPin;
  long timeOut;
};

#endif