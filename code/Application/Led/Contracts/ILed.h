#ifndef ILED_H
#define ILED_H

class ILed {
  public:  
  virtual void LightOff() = 0;
  virtual void LightOn() = 0;
};
#endif 