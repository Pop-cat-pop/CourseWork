#ifndef ALARMLEVELCHARGE_H
#define ALARMLEVELCHARGE_H

#include "IAlarm.h"     // for IAlarm
#include "IRepository.h" // for change mThresholdValueLevelCharge

class AlarmLevelCharge : public IAlarm
{
public:
  AlarmLevelCharge(float thresholdValueLevelCharge, IRepository &repository): mThresholdValueLevelCharge(thresholdValueLevelCharge), mRepository(repository)
  {
  }
  bool IsAlarm(float currentLevelCharge) override
  {
    mThresholdValueLevelCharge = mRepository.Get();
    if(mThresholdValueLevelCharge >= currentLevelCharge)
    {
      return true;
    }    
    return false;  
  }  
private:
  float mThresholdValueLevelCharge;  
  IRepository &mRepository;
};
#endif