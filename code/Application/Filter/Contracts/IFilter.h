#ifndef IFILTER_HPP
#define IFILTER_HPP

class IFilter
{
public:
  virtual float FilterValue(float value) = 0;
};

#endif