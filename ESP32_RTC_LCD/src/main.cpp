#include <Arduino.h>
#include "module_button.h"
#include "module_LED.h"
#include "module_display.h"
#include "module_rtc.h"
#include "module_eeprom.h"
#include "module_control.h"
#include "module_alarm.h"

void setup()
{
  Serial.begin(921600);
  Serial.println("Start system");
  init_EEPROM();
  read_alarm_info_from_eeprom();
  init_led_control();
  read_number_of_reset();
  init_button();   
  init_led();
  init_lcd();
  init_rtc();
}

void loop()
{ 
  check_time_return_main_screen();
  read_button();  
  read_RTC();
  display_system();
  control_with_alarm();
}