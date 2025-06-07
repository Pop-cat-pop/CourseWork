#ifndef USART_H
#define USART_H

#include "gpioaregisters.hpp"
#include "usart2registers.hpp"
#include "nvicregisters.hpp"
#include <cstring>
#include <cstdint>

class Usart
{
public:
  static Usart& Instance()
  {
    static Usart inst;
    return inst;
  }
  
  Usart() : 
    mRxBufferLength(0),
    mRxReady(false)
  {
  }
  
  void Usart::ConfigUsart()
  {
    GPIOA::MODER::MODER2::Alternate::Set();
    GPIOA::MODER::MODER3::Alternate::Set();
    GPIOA::AFRL::AFRL2::Af7::Set();
    GPIOA::AFRL::AFRL3::Af7::Set();

    USART2::CR1::OVER8::OversamplingBy16::Set();
    USART2::CR1::M::Data8bits::Set();
    USART2::CR1::PCE::ParityControlDisable::Set();
    USART2::CR2::STOP::Value0::Set();

    constexpr uint32_t SystemCoreClock = 8'000'000;
    constexpr uint32_t BaudRate        = 9'600U;
    double divisor = static_cast<double>(SystemCoreClock) / (BaudRate * 16.0);
    uint32_t mant  = static_cast<uint32_t>(divisor);
    uint32_t frac  = static_cast<uint32_t>(std::round((divisor - mant) * 16.0));
    USART2::BRR::DIV_Mantissa::Set(mant);
    USART2::BRR::DIV_Fraction::Set(frac);
    
    USART2::CR1::UE::Enable::Set();
    USART2::CR1::TE::Enable::Set();
    NVIC::ISER1::Write(1U << 6U);
  }
  
  bool IsMessageReceived() const
  {
    return mRxReady;
  }
  
  const char* GetMessage()
  {
    if (mRxReady)
    {
      mRxReady = false;
      return mRxBuffer;
    }
    return nullptr;
  }
  
  void HandleInterrupt()
  {
    // Обработка только приема данных
    if (USART2::SR::RXNE::DataReceived::IsSet())
    {
      uint8_t byte = USART2::DR::Read();
      
      if (byte == '\n' || mRxBufferLength >= mBufferCapacity - 1)
      {
        // Конец сообщения
        mRxBuffer[mRxBufferLength] = '\0';
        mRxReady = true;
        mRxBufferLength = 0;
      }
      else if (byte != '\r') // Игнорируем символ возврата каретки
      {
        mRxBuffer[mRxBufferLength++] = byte;
      }
    }
  }
  
private:
  static constexpr std::size_t mBufferCapacity = 128;
  char mRxBuffer[mBufferCapacity];  // Буфер приёма
  std::size_t mRxBufferLength;
  bool mRxReady;
};

#endif