#ifndef POTENTIOMETR_H
#define POTENTIOMETR_H

#include "ISensor.h" 
#include <algorithm>    //for std::max and min

template<typename Tport, int pinNumber>
class Potentiometr : public ISensor
{
public:    
  float GetValue() override
  {
    float percent = (static_cast<float>(GetRawData()) / 4095.0f) * 100.0f;  
    return std::max(0.0f, std::min(percent, 100.0f));
  } 
  uint16_t GetRawData() 
  {
    return Tport::IDR::Get() & (1 << pinNumber); 
  }
};
#endif 