#ifndef USART_H
#define USART_H

#include "usart2registers.hpp"  //for USART2::xxx
#include "nvicregisters.hpp"    //for NVIC::ISER1::Write(1 << 6)
#include <cstring>              //for std::string
#include <array>                //for std::array

class Usart
{
public:
  Usart()
  {
    USART2::CR1::RXNEIE::InterruptWhenRXNE::Set();
    NVIC::ISER1::Write(1 << 6);
    HandleInterrupt();
  }
  static Usart& Instance()
  {
      static Usart instance;
      return instance;   
  }

  bool IsMessageReady() const
  {
    return mMessageReady;
  }
  std::string GetMessage()
  {
    mMessageReady = false;
    auto result = std::string(mReceiveBuffer.data(), mReceiveIndex);
    mReceiveIndex = 0;
    return result;
  }
  void HandleInterrupt()
  {
    if (!USART2::SR::RXNE::DataRecieved::IsSet())
    {
      return;
    }         
    char receivedChar = static_cast<char>(USART2::DR::Get());
    if (receivedChar == '\r' || receivedChar == '\n')
    {
      if (mReceiveIndex > 0)
      {
        mReceiveBuffer[mReceiveIndex] = '\0';
        mMessageReady = true;           
      }
      return;    
    }
    if (mReceiveIndex < bufferSize - 1)
    {      
      mReceiveBuffer[mReceiveIndex++] = receivedChar;
    }
    else
    {        
      mReceiveIndex = 0;
    }
  }
private:
  static constexpr std::size_t bufferSize = 64;
  std::array<char, bufferSize> mReceiveBuffer;
  std::size_t mReceiveIndex = 0;
  bool mMessageReady = false;
};

#endif
