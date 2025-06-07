#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include "AlarmLevelCharge.h"
#include "Potentiometr.h"
#include "Filter.h"
#include "Led.h"

class TaskMeasurement()
{
public:  
  TaskMeasurement(): isFrirst(true)
  {
  }
  void static EventLed()
  {     
    if (isAlarm())
    {
      Led.Light();
    }
    else if (!isAlarm() || isFrirst)
    {
      isFrirst = false;
      Led.Toggle();
    }
  }
private:
  bool isFrirst;
};



#endif