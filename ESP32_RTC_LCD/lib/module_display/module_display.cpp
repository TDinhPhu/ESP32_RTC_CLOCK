#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "module_display.h"
#include "module_button.h"
#include "module_alarm.h"
#include "RTClib.h"


extern ALARM_INFO_t alarm_info;
uint8_t type_setting_time = TYPE_SETTING_HOUR;

uint8_t type_setting_alarm = TYPE_SETTING_NUMBER_ALARM;

extern struct tm time_setting;

uint32_t screen_display = SCREEN_DISPLAY_TIME;
uint8_t tick_counter = 0;

extern DateTime data_time;
extern BUTTON_INFO button_info[NUMBER_OF_BUTTON];
extern char daysOfTheWeek[7][12];
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

int counter = 0;
int counter2 = 0;
int counter3 = 2;

void init_lcd()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("ESP32 IOT");
  delay(1000);
  lcd.clear();
}

void display_error_init_rtc()
{
  lcd.setCursor(3, 0);
  lcd.print("ERROR RTC");
}

void display_error_rtc_not_runing()
{
  lcd.setCursor(1, 0);
  lcd.print("RTC NOT RUNING");
  delay(1000);
  lcd.clear();
}

void display_time(uint8_t col, uint8_t row, uint8_t hour, uint8_t min, uint8_t sec)
{
  lcd.setCursor(col, row);
  if (hour < 10)
  {
    lcd.print("0");
  }
  lcd.print(hour);

  lcd.print(":");

  if (min < 10)
  {
    lcd.print("0");
  }
  lcd.print(min);
  lcd.print(":");
  if (sec < 10)
  {
    lcd.print("0");
  }
  lcd.print(sec);
}

void display_date(uint8_t col, uint8_t row, uint8_t dayOfTheWeek, uint8_t day, uint8_t mon, uint16_t year)
{

  lcd.setCursor(col, row);
  lcd.print(" ");
  lcd.print(daysOfTheWeek[data_time.dayOfTheWeek()]);
  lcd.print(" ");
  if (day < 10)
  {
    lcd.print("0");
  }
  lcd.print(day);

  lcd.print("/");

  if (mon < 10)
  {
    lcd.print("0");
  }
  lcd.print(mon);
  lcd.print("/");
  if (year < 10)
  {
    lcd.print("0");
  }
  lcd.print(year);
}

void clear_lcd()
{
  lcd.clear();
}

void display_menu()
{
  display_tick(tick_counter);
  lcd.setCursor(1, 0);
  lcd.print("SET TIME");
  lcd.setCursor(1, 1);
  lcd.print("SET ALARM");
}

void display_tick(uint8_t index)
{
  if (index == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print(">");
  }
  else if (index == 1)
  {
    lcd.setCursor(0, 1);
    lcd.print(">");
  }
}

uint32_t temp_blynk = 0;
uint32_t counter_blynk = 0;
void display_number(uint32_t col, uint32_t row, uint32_t number, bool blynk)
{
  if (blynk == false)
  {
    lcd.setCursor(col, row);
    if (number < 10)
    {
      lcd.print("0");
    }
    lcd.print(number);
  }
  else if (blynk == true)
  {
    if (millis() - temp_blynk > 500)
    {
      temp_blynk = millis();
      counter_blynk++;
      if (counter_blynk % 2 == 0)
      {
        lcd.setCursor(col, row);
        lcd.print("--");
      }
      else
      {
        lcd.setCursor(col, row);
        if (number < 10)
        {
          lcd.print("0");
        }
        lcd.print(number);
      }
    }
  }
}

void display_set_time()
{
  lcd.setCursor(2, 0);
  lcd.print("SETTING TIME");
  // lcd.setCursor(0,1);
  // 0123456789012345
  // 23:40:50

  if (type_setting_time == TYPE_SETTING_HOUR)
  {
    display_number(0, 1, time_setting.tm_hour, true);
    lcd.setCursor(2, 1);
    lcd.print(":");
    display_number(3, 1, time_setting.tm_min, false);
    lcd.setCursor(5, 1);
    lcd.print(":");
    display_number(6, 1, time_setting.tm_sec, false);
  }
  else if (type_setting_time == TYPE_SETTING_MIN)
  {
    display_number(0, 1, time_setting.tm_hour, false);
    lcd.setCursor(2, 1);
    lcd.print(":");
    display_number(3, 1, time_setting.tm_min, true);
    lcd.setCursor(5, 1);
    lcd.print(":");
    display_number(6, 1, time_setting.tm_sec, false);
  }
  else if (type_setting_time == TYPE_SETTING_SEC)
  {
    display_number(0, 1, time_setting.tm_hour, false);
    lcd.setCursor(2, 1);
    lcd.print(":");
    display_number(3, 1, time_setting.tm_min, false);
    lcd.setCursor(5, 1);
    lcd.print(":");
    display_number(6, 1, time_setting.tm_sec, true);
  }
}

void display_set_date()
{
  lcd.setCursor(2, 0);
  lcd.print("SETTING DATE");

  if (type_setting_time == TYPE_SETTING_DAY)
  {
    display_number(0, 1, time_setting.tm_mday, true);
    lcd.setCursor(2, 1);
    lcd.print("/");
    display_number(3, 1, time_setting.tm_mon, false);
    lcd.setCursor(5, 1);
    lcd.print("/");
    display_number(6, 1, time_setting.tm_year, false);
  }
  else if (type_setting_time == TYPE_SETTING_MONTH)
  {
    display_number(0, 1, time_setting.tm_mday, false);
    lcd.setCursor(2, 1);
    lcd.print("/");
    display_number(3, 1, time_setting.tm_mon, true);
    lcd.setCursor(5, 1);
    lcd.print("/");
    display_number(6, 1, time_setting.tm_year, false);
  }
  else if (type_setting_time == TYPE_SETTING_YEAR)
  {
    display_number(0, 1, time_setting.tm_mday, false);
    lcd.setCursor(2, 1);
    lcd.print("/");
    display_number(3, 1, time_setting.tm_mon, false);
    lcd.setCursor(5, 1);
    lcd.print("/");
    display_number(6, 1, time_setting.tm_year, true);
  }
  else if (type_setting_time == TYPE_SETTING_DAY_OF_WEEK)
  {
    display_number(0, 1, time_setting.tm_mday, false);
    lcd.setCursor(2, 1);
    lcd.print("/");
    display_number(3, 1, time_setting.tm_mon, false);
    lcd.setCursor(5, 1);
    lcd.print("/");
    display_number(6, 1, time_setting.tm_year, false);
  }
}

// up  : tăng   a = a + 1
// down : giảm  a = a - 1
// đầu vào 1 or -1
void change_value(int8_t type_change)
{
  if (type_setting_time == TYPE_SETTING_HOUR)
  {
    time_setting.tm_hour = time_setting.tm_hour + type_change;
    if (time_setting.tm_hour > 23)
    {
      time_setting.tm_hour = 0;
    }
    else if (time_setting.tm_hour < 0)
    {
      time_setting.tm_hour = 23;
    }
  }
  else if (type_setting_time == TYPE_SETTING_MIN)
  {
    time_setting.tm_min = time_setting.tm_min + type_change;
    if (time_setting.tm_min > 59)
    {
      time_setting.tm_min = 0;
    }
    else if (time_setting.tm_min < 0)
    {
      time_setting.tm_min = 59;
    }
  }
  else if (type_setting_time == TYPE_SETTING_SEC)
  {
    time_setting.tm_sec = time_setting.tm_sec + type_change;
    if (time_setting.tm_sec > 59)
    {
      time_setting.tm_sec = 0;
    }
    else if (time_setting.tm_sec < 0)
    {
      time_setting.tm_sec = 59;
    }
  }
  else if (type_setting_time == TYPE_SETTING_DAY)
  {
    time_setting.tm_mday = time_setting.tm_mday + type_change;
    if (time_setting.tm_mday > 31)
    {
      time_setting.tm_mday = 1;
    }
    else if (time_setting.tm_mday < 1)
    {
      time_setting.tm_mday = 31;
    }
  }
  else if (type_setting_time == TYPE_SETTING_MONTH)
  {
    time_setting.tm_mon = time_setting.tm_mon + type_change;
    if (time_setting.tm_mon > 12)
    {
      time_setting.tm_mon = 1;
    }
    else if (time_setting.tm_mon < 1)
    {
      time_setting.tm_mon = 12;
    }
  }
  else if (type_setting_time == TYPE_SETTING_YEAR)
  {
    time_setting.tm_year = time_setting.tm_year + type_change;
    if (time_setting.tm_year < 2022)
    {
      time_setting.tm_year = 2022;
    }
  }
  if (screen_display == SCREEN_SET_ALARM)
  {
    write_alarm_info_to_eeprom();
    if (type_setting_alarm == TYPE_SETTING_NUMBER_ALARM)
    {
      alarm_info.data.current_alarm = alarm_info.data.current_alarm + type_change;
      if (alarm_info.data.current_alarm >= NUMBER_OF_ALARM)
      {
        alarm_info.data.current_alarm = 0;
      }
    }
    else if (type_setting_alarm == TYPE_SETTING_HOUR_START_ALARM)
    {
      alarm_info.data.alarm[alarm_info.data.current_alarm].hour_start = alarm_info.data.alarm[alarm_info.data.current_alarm].hour_start + type_change;
      if (alarm_info.data.alarm[alarm_info.data.current_alarm].hour_start >= 24)
      {
        alarm_info.data.alarm[alarm_info.data.current_alarm].hour_start = 0;
      }
      if (alarm_info.data.alarm[alarm_info.data.current_alarm].hour_start < 0)
      {
        alarm_info.data.alarm[alarm_info.data.current_alarm].hour_start = 23;
      }
    }
    else if (type_setting_alarm == TYPE_SETTING_MIN_START_ALARM)
    {
      alarm_info.data.alarm[alarm_info.data.current_alarm].min_start = alarm_info.data.alarm[alarm_info.data.current_alarm].min_start + type_change;
      if (alarm_info.data.alarm[alarm_info.data.current_alarm].min_start >= 60)
      {
        alarm_info.data.alarm[alarm_info.data.current_alarm].min_start = 0;
      }
      if (alarm_info.data.alarm[alarm_info.data.current_alarm].min_start < 0)
      {
        alarm_info.data.alarm[alarm_info.data.current_alarm].min_start = 59;
      }
    }
    else if (type_setting_alarm == TYPE_SETTING_HOUR_STOP_ALARM)
    {
      alarm_info.data.alarm[alarm_info.data.current_alarm].hour_stop = alarm_info.data.alarm[alarm_info.data.current_alarm].hour_stop + type_change;
      if (alarm_info.data.alarm[alarm_info.data.current_alarm].hour_stop >= 24)
      {
        alarm_info.data.alarm[alarm_info.data.current_alarm].hour_stop = 0;
      }
      if (alarm_info.data.alarm[alarm_info.data.current_alarm].hour_stop < 0)
      {
        alarm_info.data.alarm[alarm_info.data.current_alarm].hour_stop = 24;
      }
    }
    else if (type_setting_alarm == TYPE_SETTING_MIN_STOP_ALARM)
    {
      alarm_info.data.alarm[alarm_info.data.current_alarm].min_stop = alarm_info.data.alarm[alarm_info.data.current_alarm].min_stop + type_change;
      if (alarm_info.data.alarm[alarm_info.data.current_alarm].min_stop >= 60)
      {
        alarm_info.data.alarm[alarm_info.data.current_alarm].min_stop = 0;
      }
      if (alarm_info.data.alarm[alarm_info.data.current_alarm].min_stop < 0)
      {
        alarm_info.data.alarm[alarm_info.data.current_alarm].min_stop = 59;
      }
    }
    else if (type_setting_alarm == TYPE_SETTING_ONOFF_ALARM)
    {
      if (alarm_info.data.alarm[alarm_info.data.current_alarm].status == true)
      {
        alarm_info.data.alarm[alarm_info.data.current_alarm].status = false;
      }
      else
      {

        alarm_info.data.alarm[alarm_info.data.current_alarm].status = true;
      }
    }
    else if (type_setting_alarm == TYPE_SETTING_DAY_OF_WEEK)
    {
      time_setting.tm_wday = time_setting.tm_wday + type_change;
      if (time_setting.tm_wday > 6)
      {
        time_setting.tm_wday = 0;
      }
      if (time_setting.tm_wday < 0)
      {
        time_setting.tm_wday = 6;
      }
    }
  }
}

void display_set_alarm()
{
  lcd.setCursor(0, 0);
  lcd.print("Alarm:");
  if (type_setting_alarm == TYPE_SETTING_NUMBER_ALARM)
  {
    display_number(6, 0, alarm_info.data.current_alarm, true);
  }
  else
  {
    display_number(6, 0, alarm_info.data.current_alarm, false);
  }

  if (type_setting_alarm == TYPE_SETTING_ONOFF_ALARM)
  {
    if (alarm_info.data.alarm[alarm_info.data.current_alarm].status == 1)
    {
      lcd.setCursor(10, 0);
      lcd.print("ON ");
    }
    else
    {
      lcd.setCursor(10, 0);
      lcd.print("OFF");
    }
  }

  if (type_setting_alarm == TYPE_SETTING_HOUR_START_ALARM)
  {
    display_number(0, 1, alarm_info.data.alarm[alarm_info.data.current_alarm].hour_start, true);
  }
  else
  {
    display_number(0, 1, alarm_info.data.alarm[alarm_info.data.current_alarm].hour_start, false);
  }

  lcd.setCursor(2, 1);
  lcd.print(":");

  if (type_setting_alarm == TYPE_SETTING_MIN_START_ALARM)
  {
    display_number(3, 1, alarm_info.data.alarm[alarm_info.data.current_alarm].min_start, true);
  }
  else
  {
    display_number(3, 1, alarm_info.data.alarm[alarm_info.data.current_alarm].min_start, false);
  }

  lcd.setCursor(5, 1);
  lcd.print(" ");

  if (type_setting_alarm == TYPE_SETTING_DAY_OF_WEEK)
  {
    if (time_setting.tm_wday == 0)
    {
      lcd.setCursor(6, 1);
      lcd.print("Sun");
    }
    else if (time_setting.tm_wday == 1)
    {
      lcd.setCursor(6, 1);
      lcd.print("Mon");
    }
    else if (time_setting.tm_wday == 2)
    {
      lcd.setCursor(6, 1);
      lcd.print("Tue");
    }
    else if (time_setting.tm_wday == 3)
    {
      lcd.setCursor(6, 1);
      lcd.print("Wed");
    }
    else if (time_setting.tm_wday == 4)
    {
      lcd.setCursor(6, 1);
      lcd.print("Thu");
    }
    else if (time_setting.tm_wday == 5)
    {
      lcd.setCursor(6, 1);
      lcd.print("Fri");
    }
    else if (time_setting.tm_wday == 6)
    {
      lcd.setCursor(6, 1);
      lcd.print("Sat");
    }
  }

  if (type_setting_alarm == TYPE_SETTING_HOUR_STOP_ALARM)
  {
    display_number(10, 1, alarm_info.data.alarm[alarm_info.data.current_alarm].hour_stop, true);
  }
  else
  {
    display_number(10, 1, alarm_info.data.alarm[alarm_info.data.current_alarm].hour_stop, false);
  }
  lcd.setCursor(12, 1);
  lcd.print(":");

  if (type_setting_alarm == TYPE_SETTING_MIN_STOP_ALARM)
  {
    display_number(13, 1, alarm_info.data.alarm[alarm_info.data.current_alarm].min_stop, true);
  }
  else
  {
    display_number(13, 1, alarm_info.data.alarm[alarm_info.data.current_alarm].min_stop, false);
  }
}

void display_system()
{
  switch (screen_display)
  {
  case SCREEN_DISPLAY_TIME:
    display_time(6, 1, data_time.hour(), data_time.minute(), data_time.second());
     display_date(2, 2, data_time.dayOfTheWeek(), data_time.day(), data_time.month(), data_time.year());
    break;
  case SCREEN_MENU:
    display_menu();
    break;
  case SCREEN_SET_TIME:
    display_set_time();
    break;
  case SCREEN_SET_DATE:
    display_set_date();
    break;
  case SCREEN_SET_ALARM:
    display_set_alarm();
    break;
  default:
    break;
  }
}

uint32_t temp_time_return = 0;
uint32_t counter_second = 0;
void check_time_return_main_screen()
{
  if (millis() - temp_time_return > 1000) // 1s
  {
    temp_time_return = millis();
    counter_second++;
    // Serial.printf("counter_second : %d \r\n",counter_second);
    if ((counter_second > 15) && (screen_display != SCREEN_DISPLAY_TIME))
    {
      Serial.println("Return main screen");
      clear_lcd();
      screen_display = SCREEN_DISPLAY_TIME;
    }
  }
}

void clear_time_return_main_screen()
{
  counter_second = 0;
}
