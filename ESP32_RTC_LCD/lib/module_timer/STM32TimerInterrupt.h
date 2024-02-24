
#ifndef STM32_TIMER_INTERRUPT_VERSION
  #define STM32_TIMER_INTERRUPT_VERSION       "STM32TimerInterrupt v1.2.0"
#endif

#include "TimerInterrupt_Generic_Debug.h"

class STM32TimerInterrupt;

typedef STM32TimerInterrupt STM32Timer;

typedef void (*timerCallback)  ();


class STM32TimerInterrupt
{
  private:
    TIM_TypeDef*    _timer;
    HardwareTimer*  _hwTimer = NULL;

    timerCallback   _callback;        // pointer to the callback function
    float           _frequency;       // Timer frequency
    uint32_t        _timerCount;      // count to activate timer

  public:

    STM32TimerInterrupt(TIM_TypeDef* timer)
    {
      _timer = timer;
      
      _hwTimer = new HardwareTimer(_timer);
      
      _callback = NULL;
    };
    
    ~STM32TimerInterrupt()
    {
      if (_hwTimer)
        delete _hwTimer;
    }

    // frequency (in hertz) and duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    // No params and duration now. To be addes in the future by adding similar functions here or to STM32-hal-timer.c
    bool setFrequency(float frequency, timerCallback callback)
    {
      // select timer frequency is 1MHz for better accuracy. We don't use 16-bit prescaler for now.
      // Will use later if very low frequency is needed.
      _frequency  = 1000000;
      _timerCount = (uint32_t) _frequency / frequency;
      
      TISR_LOGWARN1(F("STM32TimerInterrupt: Timer Input Freq (Hz) ="), _hwTimer->getTimerClkFreq());
      TISR_LOGWARN3(F("Frequency ="), _frequency, F(", _count ="), (uint32_t) (_timerCount));


      _hwTimer->setCount(0, MICROSEC_FORMAT);
      _hwTimer->setOverflow(_timerCount, MICROSEC_FORMAT);

      _hwTimer->attachInterrupt(callback);
      _hwTimer->resume();

      return true;
    }

    // interval (in microseconds) and duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    // No params and duration now. To be addes in the future by adding similar functions here or to STM32-hal-timer.c
    bool setInterval(unsigned long interval, timerCallback callback)
    {
      return setFrequency((float) (1000000.0f / interval), callback);
    }

    bool attachInterrupt(float frequency, timerCallback callback)
    {
      return setFrequency(frequency, callback);
    }

    // interval (in microseconds) and duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    // No params and duration now. To be addes in the future by adding similar functions here or to STM32-hal-timer.c
    bool attachInterruptInterval(unsigned long interval, timerCallback callback)
    {
      return setFrequency( (float) ( 1000000.0f / interval), callback);
    }

    void detachInterrupt()
    {
      _hwTimer->detachInterrupt();
    }

    void disableTimer()
    {
      //_hwTimer->detachInterrupt();
      _hwTimer->pause();
    }

    // Duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    void reattachInterrupt()
    {
      setFrequency(_frequency, _callback);
    }

    // Duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    void enableTimer()
    {
      //setFrequency(_frequency, _callback);
      _hwTimer->setCount(0, MICROSEC_FORMAT);
      _hwTimer->resume();
    }

    // Just stop clock source, clear the count
    void stopTimer()
    {
      _hwTimer->pause();
      _hwTimer->setCount(0, MICROSEC_FORMAT);
    }

    // Just reconnect clock source, start current count from 0
    void restartTimer()
    {
      _hwTimer->setCount(0, MICROSEC_FORMAT);
      _hwTimer->resume();
    }
}; // class STM32TimerInterrupt



