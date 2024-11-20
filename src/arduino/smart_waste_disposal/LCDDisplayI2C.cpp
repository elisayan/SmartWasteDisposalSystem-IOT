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

void LCDDisplayI2C::enterWaste() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PRESS OPEN TO ENTER WASTE");
}

void LCDDisplayI2C::pressClose() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PRESS CLOSE WHEN DONE");
}

void LCDDisplayI2C::wasteReceived() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WASTE RECEIVED");
}

void LCDDisplayI2C::containerFull() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CONTAINER FULL");
}

void LCDDisplayI2C::problemDetected() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PROBLEM DETECTED");
}
