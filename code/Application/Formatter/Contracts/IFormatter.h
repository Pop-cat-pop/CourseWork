#ifndef IFORMATTER_HPP
#define IFORMATTER_HPP

#include <cstdint> // for std::uint8_t
#include <string>

class IFormatter
{
public:
  virtual float Convert(std::string& str) = 0;
};

#endif