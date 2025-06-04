#ifndef FILTER_HPP
#define FILTER_HPP

#include "IFilter.h" // for IFilter
#include <cmath> // for std::exp

class Filter : public IFilter
{
public:
  Filter(const float& dt, const float& rc) : dt(dt), rc(rc), oldValue(0.0f), isFirstTime(true)  
  {
  }
  
  float FilterValue(float value) override
  {
    if (isFirstTime)
    {
      oldValue = value;
      isFirstTime = false;
      return value;
    }
    
    float tau = 1.0f - std::exp(-dt / rc);
    float filteredValue = oldValue + (value - oldValue) * tau;
    oldValue = filteredValue;
    return filteredValue;
  }



private:
  const float& dt;
  const float& rc;
  float oldValue;
  bool isFirstTime;
};

#endif
