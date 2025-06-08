#ifndef IALARM_H
#define IALARM_H

class IAlarm
{
public:
  virtual bool IsAlarm(float currentLevelCharge) = 0;
};
#endif