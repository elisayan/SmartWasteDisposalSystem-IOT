#ifndef __LCD_DISPLAY_I2C__
#define __LCD_DISPLAY_I2C__

#include <LiquidCrystal_I2C.h>
#include "LCDDisplay.h"

class LCDDisplayI2C : public LCDDisplay {
public:
  LCDDisplayI2C();
  void setMessage(char* text);

private:
  LiquidCrystal_I2C lcd;
};

#endif