#ifndef POTENTIOMETR_H
#define POTENTIOMETR_H

#include "ISensor.h"            //for ISensor
#include "adc1registers.hpp"    //for ADC1::CR2::SWSTART::On::Set()
#include <algorithm>            //for std::max and min

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
    ADC1::CR2::SWSTART::On::Set();
    return ADC1::DR::DATA::Get();
  }
};
#endif 
