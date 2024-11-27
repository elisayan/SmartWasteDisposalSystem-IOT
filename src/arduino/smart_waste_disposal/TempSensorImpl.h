#ifndef __TEMP_SENSOR_LM35__
#define __TEMP_SENSOR_LM35__

class TempSensorTMP36: public TempSensor {

public:
  TempSensorTMP36(int pin);	
  virtual float getTemperature();
  
private:
  int pin;
};


#endif
