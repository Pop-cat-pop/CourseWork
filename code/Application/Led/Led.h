#ifndef LED_H
#define LED_H

#include "ILed.h" // for ILed

template<typename Tport, int pinNumber> //Led<GPIOA, 5>
class Led : public ILed
{
public:        
  void LightOff() override
  {
    LightOn();
    Toggle();
  }
  void LightOn() override
  {
    Tport::ODR::Set(1 << pinNumber); 
  } 
  void Toggle()
  {
    Tport::ODR::Toggle(1 << pinNumber);
  }
};
#endif