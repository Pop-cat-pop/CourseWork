#include "rtos.hpp"         // for Rtos
#include "mailbox.hpp"      // for Mailbox
#include "event.hpp"        // for Event

#include "Config.h"                     // for Config.registers_õõõ()
#include "Led.h"                        // for Led<GPIOA, 5>
#include "Filter.h"                     // for Filter filter(dt, rc)        
#include "AlarmLevelCharge.h"           // for AlarmLevelCharge alarm       
#include "Potentiometr.h"               // for Potentiometr potentiometr
#include "Formatter.h"                  // for Formatter formatter
#include "Measurement.h"                // for Measurement measurement
#include "Usart.h"                      // for Usart usart
#include "Repository.h"                 // for Repository repository
#include "TaskMeasurement.h"            // for TaskMeasurement
#include "TaskUsart.h"                  // for TaskUsart

std::uint32_t SystemCoreClock = 8'000'000U;
Config config;

extern "C" {
  int __low_level_init(void)
  {
    config.registers_RCC();
    config.registers_GPIO();
    config.registers_ADC();
    config.registers_USART();
    return 1;
  }
}

Led<GPIOA, 5> led;
Potentiometr potentiometr;

constexpr auto dt = 0.1f;
constexpr auto rc = 1.0f;
Filter filter(dt, rc);

Usart usart;
Formatter formatter(usart);
Repository repository;
TaskUsart taskUsart(formatter, usart, repository);
AlarmLevelCharge alarm(50.0f, repository);
Measurement measurement(alarm, filter, potentiometr, led);
OsWrapper::Event event{500ms, 1};
TaskMeasurement taskMeashurement(measurement);

int main()
{
  using namespace OsWrapper;
  Rtos::CreateThread(taskMeashurement, "taskMeashurement", ThreadPriority::normal);
  Rtos::CreateThread(taskUsart, "taskUsart", ThreadPriority::lowest);
  Rtos::Start();
  return 0;
}
