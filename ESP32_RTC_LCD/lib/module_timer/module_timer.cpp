#include <Arduino.h>
#include "STM32TimerInterrupt.h"
#include "module_timer.h"


uint32_t ui32_counter_timer_1_second = 0;

// Init STM32 timer TIM1
STM32Timer ITimer0(TIM1);

// Init STM32 timer TIM2
STM32Timer ITimer1(TIM2);

void TimerHandler0()
{ 
  ui32_counter_timer_1_second++;

  Serial.pỉ
}

void TimerHandler1()
{
  //Serial.println("timer 1 ");
}


void init_timer()
{  
  // Interval in microsecs
  if (ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0))
  {
    Serial.println("Starting ITimer0 OK");   
  }
  else
  {
      Serial.println("Can't set ITimer0. Select another freq. or timer");
  }
    
  // Interval in microsecs
  if (ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS * 1000, TimerHandler1))
  {
    Serial.println("Starting ITimer1 OK");
  }
  else
  {
      Serial.println("Can't set ITimer1. Select another freq. or timer");
  }  
}
