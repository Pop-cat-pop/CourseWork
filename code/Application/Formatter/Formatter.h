#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <string>               // for string
#include <stdexcept>            // for find('.')
#include "TaskUsart.h"          // for string from comp
#include "IFormatter.h"         // for IFormatter
#include "Usart.h"              // for Usart

class Formatter : public IFormatter
{
public:
  Formatter(Usart &usart) : mUsart(usart)
  {
  }
    float Convert(std::string& mStr) override
    {
      if (mStr.empty()) {
         return 0;
      }
      float result = 0.0f;
      size_t dot_pos = mStr.find('.');
      bool has_decimal = (dot_pos != std::string::npos);
      if (mStr.find('.', dot_pos + 1) != std::string::npos) {
        return 0;
      }
      std::string integer_part = has_decimal ? mStr.substr(0, dot_pos) : mStr;
      for (char c : integer_part) {
        if (!isdigit(c)) {
          break;
        }
        result = result * 10 + (c - '0');
      }
      if (has_decimal) 
      {          
        std::string fractional_part = mStr.substr(dot_pos + 1);
        if (fractional_part.empty()) 
        {
            return 0;
        }
        float fraction = 0.0f;
        float divisor = 10.0f;
        
        for (char c : fractional_part) 
        {
          if (!isdigit(c)) 
          {
            break;
          }
          fraction += (c - '0') / divisor;
          divisor *= 10;
        }
        result += fraction;
      }
      return result;
    }    
private: 
  Usart &mUsart;
  std::string mStr = mUsart.GetMessage();
};

#endif