#include "LCDDisplayI2C.h"

LCDDisplayI2C::LCDDisplayI2C() : lcd(0x27, 20, 4) { 
  lcd.init();
  lcd.backlight();
}

void LCDDisplayI2C::setMessage(char* text) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text);
}
