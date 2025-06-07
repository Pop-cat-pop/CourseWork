#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include "IAlarm.h"     // for IAlarm 
#include "IFilter.h"    // for IFilter 
#include "ISensor.h"    // for ISensor 
#include "ILed.h"       // for ILed         

class Measurement  
{
public:  
  Measurement (IAlarm &alarm, IFilter &filter, ISensor &sensor, ILed &led): changePosition(true), mAlarm(alarm), mFilter(filter), mSensor(sensor), mLed(led)
  {
  }
  void EventLed()
  {   
    auto currentValue = mFilter.FilterValue(mSensor.GetValue());
    
    if (mAlarm.IsAlarm(currentValue) && changePosition)
    {
      mLed.LightOn();
      changePosition = false;
    }
    else if (!mAlarm.IsAlarm(currentValue) && (changePosition == false))
    {
      mLed.LightOff();
      changePosition = true;
    }
  }
private:
  bool changePosition;
  IAlarm &mAlarm; 
  IFilter &mFilter;
  ISensor &mSensor;
  ILed &mLed;
  
};


#endif