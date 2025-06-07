#ifndef TASKMEASUREMENT_H
#define TASKMEASUREMENT_H

#include "Measurement.h"        // for Measurement
#include "thread.hpp"           // for OsWrapper::Thread     

class TaskMeasurement : public OsWrapper::Thread<512U>
{
public: 
  TaskMeasurement(Measurement &measurement) : mMeasurement(measurement)
  {
  }
  void Execute() override
  {
    for(;;)
    {
      mMeasurement.EventLed();
      SleepUntil(50ms);    
    } 
  }
private:
  Measurement &mMeasurement;
};
#endif