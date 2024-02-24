#include <Arduino.h>
#include "module_button.h"
#include "module_display.h"
#include "module_rtc.h"
#include "module_alarm.h"

extern ALARM_INFO_t alarm_info;
extern struct tm time_setting;

extern uint8_t type_setting_time ;
extern uint8_t type_setting_alarm;

extern uint32_t screen_display;

extern uint8_t tick_counter;
int list_gpio_button[NUMBER_OF_BUTTON] = {GPIO_BUTTON_1, GPIO_BUTTON_2, GPIO_BUTTON_3, GPIO_BUTTON_4};


BUTTON_INFO button_info[NUMBER_OF_BUTTON];

uint8_t type_setting = CHOOSE_SET_TIME;

void init_button()
{
    for (size_t i = 0; i < NUMBER_OF_BUTTON; i++)
    {
        pinMode(list_gpio_button[i], INPUT_PULLUP);
    }
}

void read_button()
{
    for (size_t i = 0; i < NUMBER_OF_BUTTON; i++)
    {
        if (digitalRead(list_gpio_button[i]) == false)
        {
            delay(150);
            if (digitalRead(list_gpio_button[i]) == false)
            {                
                button_info[i].status = true;
                button_info[i].counter_press = button_info[i].counter_press + 1;
                Serial.printf("Bạn đã nhấn phím %d \r\n", i + 1);
                if(i == BUTTON_ENTER)
                {
                    Serial.println("Enter button");
                    clear_time_return_main_screen();
                    if (screen_display == SCREEN_DISPLAY_TIME)
                    {
                        clear_lcd();
                        screen_display = SCREEN_MENU;
                    }   
                    else if (screen_display == SCREEN_MENU)
                    {
                        if (type_setting == CHOOSE_SET_ALARM)
                        {
                            clear_lcd();
                            Serial.println("start set larm");
                            screen_display = SCREEN_SET_ALARM;
                            type_setting_alarm = TYPE_SETTING_NUMBER_ALARM;
                            alarm_info.data.current_alarm = 0;
                        }
                        else if (type_setting == CHOOSE_SET_TIME)
                        {
                            clear_lcd();
                            Serial.println("start set time");
                            get_current_time_to_setting();
                            screen_display = SCREEN_SET_TIME;
                        }                           
                    }
                    else if (screen_display == SCREEN_SET_TIME)
                    {
                        if (type_setting_time == TYPE_SETTING_HOUR)
                        {
                            Serial.println("set min");
                            type_setting_time = TYPE_SETTING_MIN;
                        }
                        else if (type_setting_time == TYPE_SETTING_MIN)
                        {
                            Serial.println("set sec");
                            type_setting_time = TYPE_SETTING_SEC;
                        }
                        else if (type_setting_time == TYPE_SETTING_SEC)
                        {
                            Serial.println("save time -> go to set date");
                            set_date_time(time_setting.tm_wday,time_setting.tm_hour,time_setting.tm_min,time_setting.tm_sec,time_setting.tm_mday,time_setting.tm_mon,time_setting.tm_year);
                            clear_lcd();
                            type_setting_time = TYPE_SETTING_DAY;
                            screen_display = SCREEN_SET_DATE;
                        }                        
                    }   
                    else if (screen_display == SCREEN_SET_DATE)
                    {
                        if (type_setting_time == TYPE_SETTING_DAY)
                        {
                            Serial.println("set month");
                            type_setting_time = TYPE_SETTING_MONTH;
                        }
                        else if (type_setting_time == TYPE_SETTING_MONTH)
                        {
                            Serial.println("set year");
                            type_setting_time = TYPE_SETTING_YEAR;
                        }
                        else if (type_setting_time == TYPE_SETTING_YEAR)
                        {
                             Serial.println("set dayoftheweek");
                            type_setting_time = TYPE_SETTING_DAY_OF_WEEK;
                        }
                        else if (type_setting_time == TYPE_SETTING_DAY_OF_WEEK)
                        {
                            Serial.println("save time -> done");
                            set_date_time(time_setting.tm_wday,time_setting.tm_hour,time_setting.tm_min,time_setting.tm_sec,time_setting.tm_mday,time_setting.tm_mon,time_setting.tm_year);
                            clear_lcd();
                            screen_display = SCREEN_DISPLAY_TIME;
                        }                        
                    }
                    else if (screen_display == SCREEN_SET_ALARM)
                    {
                        if (type_setting_alarm == TYPE_SETTING_NUMBER_ALARM)
                        {
                            Serial.println("set on or off");
                            type_setting_alarm = TYPE_SETTING_ONOFF_ALARM;

                        }
                        else if (type_setting_alarm == TYPE_SETTING_ONOFF_ALARM)
                        {
                            Serial.println("set hour start");
                            type_setting_alarm = TYPE_SETTING_HOUR_START_ALARM;
                        }
                        else if (type_setting_alarm == TYPE_SETTING_HOUR_START_ALARM)
                        {
                            Serial.println("set min start");
                            type_setting_alarm = TYPE_SETTING_MIN_START_ALARM;
                        }
                        else if (type_setting_alarm == TYPE_SETTING_MIN_START_ALARM)
                        {
                            Serial.println("set day of week");
                            type_setting_alarm = TYPE_SETTING_DAY_OF_WEEK;
                        }
                        else if (type_setting_alarm == TYPE_SETTING_DAY_OF_WEEK)
                        {
                            Serial.println("set hour stop");
                            type_setting_alarm = TYPE_SETTING_HOUR_STOP_ALARM;
                        }
                        else if (type_setting_alarm == TYPE_SETTING_HOUR_STOP_ALARM)
                        {
                            Serial.println("set min stop");
                            type_setting_alarm = TYPE_SETTING_MIN_STOP_ALARM;
                        }
                        else if (type_setting_alarm == TYPE_SETTING_MIN_STOP_ALARM)
                        {
                            
                            Serial.printf("SETTING ALARM : %d ",alarm_info.data.current_alarm);
                            alarm_info.data.current_alarm++;
                            type_setting_alarm = TYPE_SETTING_NUMBER_ALARM;
                            if (alarm_info.data.current_alarm == NUMBER_OF_ALARM)
                            {
                                Serial.println("DONE ALL ALARM");
                                clear_lcd();
                                screen_display = SCREEN_DISPLAY_TIME;
                            }
                            
                        }

                    }
                    



                }
                else if(i == BUTTON_EXIT)
                {
                    Serial.println("Exit button");
                    clear_time_return_main_screen();
                    if (screen_display == SCREEN_MENU)
                    {
                        clear_lcd();
                        screen_display = SCREEN_DISPLAY_TIME;
                    }  
                    else if ((screen_display == SCREEN_SET_ALARM) || (screen_display == SCREEN_SET_TIME) || (screen_display == SCREEN_SET_DATE))  
                    {
                        clear_lcd();
                        screen_display = SCREEN_MENU;
                    }
                                     
                }
                else if(i == BUTTON_UP)
                {
                    clear_time_return_main_screen();
                    if (screen_display == SCREEN_MENU)
                    {
                        clear_lcd();
                        type_setting = CHOOSE_SET_TIME;
                        tick_counter = 0;
                    }  
                    else if (screen_display == SCREEN_SET_TIME)
                    {
                        change_value(1);
                    }  
                    else if (screen_display == SCREEN_SET_DATE)
                    {
                        change_value(1);
                    }  
                    else if (screen_display == SCREEN_SET_ALARM)
                    {
                        change_value(1);
                    }                                      
                }
                else if(i == BUTTON_DOWN)
                {
                    clear_time_return_main_screen();
                    if (screen_display == SCREEN_MENU)
                    {
                        clear_lcd();
                        type_setting = CHOOSE_SET_ALARM;
                        tick_counter = 1;
                    } 
                    else if (screen_display == SCREEN_SET_TIME)
                    {
                        change_value(-1);
                    }   
                    else if (screen_display == SCREEN_SET_DATE)
                    {
                        change_value(-1);
                    }  
                    else if (screen_display == SCREEN_SET_ALARM)
                    {
                        change_value(-1);
                    }  

                }
            }
        }
    }

}