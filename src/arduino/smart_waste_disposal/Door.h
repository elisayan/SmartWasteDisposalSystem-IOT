#ifndef __DOOR__
#define __DOOR__

class Door {

public:
  virtual void on() = 0;
  virtual void setPosition(int angle) = 0;
  virtual void off() = 0;
};

#endif
