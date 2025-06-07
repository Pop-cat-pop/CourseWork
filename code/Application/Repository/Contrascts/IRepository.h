#ifndef IREPOSITORY_H
#define IREPOSITORY_H

class IRepository
{
public:
  virtual float Get() = 0;
  virtual void Set(float newValue) = 0;
};
#endif
