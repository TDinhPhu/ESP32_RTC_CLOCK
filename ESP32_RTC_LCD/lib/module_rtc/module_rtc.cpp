#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include "module_display.h"
#include "RTClib.h"
#include "module_rtc.h"
#include <time.h>

struct tm time_setting;



RTC_DS1307 rtc;
DateTime data_time;

extern LiquidCrystal_I2C lcd; 

char daysOfTheWeek[7][12] = {"Sun","Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void init_rtc()
{ 
  if (! rtc.begin()) 
  {
    Serial.println("Couldn't find RTC");
    while (1)
    {
      display_error_init_rtc();
    }
  }

  if (!rtc.isrunning()) 
  {
    Serial.println("RTC is NOT running!");
    display_error_rtc_not_runing();

  }
  // set_date_time(19,50,30,24,9,2023);
  rtc.adjust(DateTime(2023, 10, 10, 20, 47, 20));
}

uint32_t temp_read_RTC = 0;
void read_RTC()
{
  if (millis() - temp_read_RTC > TIME_READ_RTC)
  {
    temp_read_RTC = millis();   
    data_time =  rtc.now(); 
    print_data_time();   
  }
}

void print_data_time()
{
  Serial.print(data_time.hour());
  Serial.print(':');
  Serial.print(data_time.minute());
  Serial.print(':');
  Serial.print(data_time.second());
  Serial.print("   ");
  Serial.print(daysOfTheWeek[data_time.dayOfTheWeek()]);
  Serial.print("  ");
  Serial.print(data_time.day());
  Serial.print('/');
  Serial.print(data_time.month());
  Serial.print('/');
  Serial.print(data_time.year());
  Serial.println();
}

void set_date_time(char daysOfTheWeek, uint8_t hour, uint8_t min, uint8_t sec,uint8_t day, uint8_t month, uint16_t year)
{
  rtc.adjust(DateTime(year, month, day, hour, min, sec));
}

void get_current_time_to_setting()
{
  time_setting.tm_hour = data_time.hour();
  time_setting.tm_min = data_time.minute();
  time_setting.tm_sec = data_time.second();
  time_setting.tm_mday = data_time.day();
  time_setting.tm_mon = data_time.month();
  time_setting.tm_year = data_time.year();
  time_setting.tm_wday = data_time.dayOfTheWeek();
}