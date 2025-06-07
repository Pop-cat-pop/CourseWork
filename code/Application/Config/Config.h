#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>                      // for std
#include "rccregisters.hpp"             // for RCC
#include "gpiocregisters.hpp"           // for GPIOC
#include "nvicregisters.hpp"            // for NVIC
#include "extiregisters.hpp"            // for EXTI
#include "syscfgregisters.hpp"          // for CFGR
#include "tim5registers.hpp"            // for TIM5
#include "gpioaregisters.hpp"           // for GPIOA

#include "gpioaregisters.hpp"
#include "usart2registers.hpp"
#include "nvicregisters.hpp"
#include "adc1registers.hpp"

#include "TaskUsart.h"                  // for TaskUsart.HandleInterrupt();


class Config
{
public:
  void registers_RCC()
  {
    //Switch on external 8 MHz oscillator
    RCC::CR::HSEON::On::Set();
    while (RCC::CR::HSERDY::NotReady::IsSet())
    {
    }
    //Switch system clock on external oscillator
    RCC::CFGR::SW::Hse::Set();
    while (!RCC::CFGR::SWS::Hse::IsSet())
    {
    }
    RCC::CR::HSION::Off::Set();   
    //Switch on clock on PortA
    RCC::AHB1ENR::GPIOAEN::Enable::Set();   
    RCC::APB2ENR::SYSCFGEN::Enable::Set();
    // RCC on ADC
    RCC::APB2ENR::ADC1EN::Enable::Set();
    // RCC on USART2
    RCC::APB1ENR::USART2EN::Enable::Set();
  }
  
  void registers_GPIO()
  {
    //LED1 on PortA.5, set PortA.5 as output
    GPIOA::MODER::MODER5::Output::Set();   
    // Potentiometer on Port A0
    GPIOA::MODER::MODER0::Analog::Set();  
    GPIOA::MODER::MODER2::Alternate::Set();
    GPIOA::MODER::MODER3::Alternate::Set();
    GPIOA::AFRL::AFRL2::Af7::Set();
    GPIOA::AFRL::AFRL3::Af7::Set();
  }
  
  void registers_ADC()
  {  
    ADC1::CR1::RES::Bits12::Set();                      // 12-битное разрешение
    ADC1::CR2::EOCS::SingleConversion::Set();           // Флаг EOC после каждого преобразования
    ADC1::CR1::SCAN::Enable::Set();
    ADC1::CR2::DMA::Disable::Set();                     //Выключение DMA
    ADC1::CR2::CONT::SingleConversion::Set();           // Одиночное преобразование (без DMA)
    ADC1::SQR1::L::Conversions1::Set();                 // 1 канал в последовательности
    ADC1::SQR3::SQ1::Channel0::Set();                   // Канал 0 (PA0)
    ADC1::SMPR2::SMP0::Cycles480::Set();                // Время выборки (для большей точности)
    ADC1::CR2::ADON::Enable::Set();                     // Первое включение   
  } 
  
  void registers_USART()
  {
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
    USART2::CR1::RE::Enable::Set(); 
  }
private:
  std::uint32_t SystemCoreClock = 8'000'000U;
};

#endif
