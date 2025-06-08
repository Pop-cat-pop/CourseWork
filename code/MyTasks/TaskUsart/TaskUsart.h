#ifndef TASKUSART_H
#define TASKUSART_H
      
#include "Usart.h"                      // for Usart
#include "IFormatter.h"                 // for IFormatter
#include "thread.hpp"                   // for OsWrapper::Thread
#include "IRepository.h"                // for IRepository

class TaskUsart : public OsWrapper::Thread<512U>
{
public: 
  TaskUsart(IFormatter &formatter, Usart &usart, IRepository &repository) : mFormatter(formatter), mUsart(usart), mRepository(repository)
  {
  }  
  void GetToRepositoryUsartValue()
  {
    auto message = mUsart.GetMessage();
    auto formatMessage = mFormatter.Convert(message);
    mRepository.Set(formatMessage);
  }
  void Execute() override
  {
    for(;;)
    {
      if (mUsart.IsMessageReady())
      {
        GetToRepositoryUsartValue();               
      }
      SleepUntil(50ms);  
    } 
  } 
private:
  std::string UsartValue;
  Usart &mUsart;
  IFormatter &mFormatter;
  IRepository &mRepository;
};

#endif
