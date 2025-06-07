#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "IRepository.h" //for IRepository

class Repository : public IRepository
{
public:
  float Get() override
  {
    return value;
  }
  void Set(float newValue) override
  {
    value = newValue;
  }
private:
  float value;
};

#endif