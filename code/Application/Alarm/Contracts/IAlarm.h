#ifndef IALARM_H
#define IALARM_H

class IAlarm
{
public:
  virtual bool IsAlarm(float CurrentValue, float ThresholdValue) = 0;
};


#endif