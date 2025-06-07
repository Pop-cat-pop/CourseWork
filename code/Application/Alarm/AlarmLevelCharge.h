#ifndef ALARMLEVELCHARGE_H
#define ALARMLEVELCHARGE_H

#include "IAlarm.h"

extern float ThresholdValueLevelCharge;

class AlarmLevelCharge : public IAlarm
{
public:
  AlarmLevelCharge(float CurrentLevelCharge): CurrentLevelCharge(CurrentLevelCharge), ThresholdValueLevelCharge(10.0f)
  {
  }
  bool IsAlarm(float CurrentLevelCharge, float ThresholdValueLevelCharge) override
  {
    if(ThresholdValueLevelCharge >= CurrentLevelCharge)
    {
      return true;
    }
    return false;
  } 
private:
  float CurrentLevelCharge; 
  float ThresholdValueLevelCharge;   
};
#endif