#ifndef ILED_H
#define ILED_H

class ILed {
  public:
  virtual void Light() = 0;
  virtual void Toggle() = 0;
};



#endif 