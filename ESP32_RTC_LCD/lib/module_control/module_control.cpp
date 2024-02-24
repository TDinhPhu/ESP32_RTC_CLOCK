#include <Arduino.h>
#include "module_control.h"
#include "module_alarm.h"
#include "RTClib.h"
#include "module_rtc.h"

extern struct tm time_setting;
extern DateTime data_time;
extern ALARM_INFO_t alarm_info;
// kiểm tra xem thử alarm nào được bật
// nếu được bật thì kiểm trra đã đúng thời gian để kích hoạt 
// nếu đã kích hoạt thì xem đã đúng giờ để dừng chưa

// có tất cả 10 timer  ->> dùng vòng for  



void init_led_control()
{
    pinMode(GPIO_LED,OUTPUT);
    digitalWrite(GPIO_LED,LOW);
}

void turn_on_led()
{
    digitalWrite(GPIO_LED,HIGH);
}
void turn_off_led()
{
    digitalWrite(GPIO_LED,LOW);
}

uint32_t time_temp_control = 0;
void control_with_alarm() 
{
    // total : 2 alarms
    // 1:   start : 8:30   - stop: 9:30
    // 2    start : 9:00     stop 10h45  10h46

    bool have_timer_work = false;
    if (millis() - time_temp_control > 1000)
    {
        time_temp_control = millis();

        for (size_t i = 0; i < NUMBER_OF_ALARM ;i++) // 10 giá trị từ 0 - 9
        {
            if (alarm_info.data.alarm[i].status ==  true)
            {
                Serial.printf("Alarm %d is ON \r\n",i);
                // alarm này đã bật. - >>> so sánh thời gian xem đã đúng giờ chưa để hoạt động
                // ví dụ : start : 8:20        stop  11:30
                if ((data_time.hour() >= alarm_info.data.alarm[i].hour_start ) && (data_time.minute() >= alarm_info.data.alarm[i].min_start ) && (data_time.dayOfTheWeek() == time_setting.tm_wday))
                {
                    // bắt đầu alarm -----
                    // kiểm tra đủ điều điều kiện stop
                    if ((data_time.hour() >= alarm_info.data.alarm[i].hour_stop ) && (data_time.minute() >= alarm_info.data.alarm[i].min_stop)&& (data_time.dayOfTheWeek() != time_setting.tm_wday))
                    {
                        Serial.println("turn off led");
                        //turn_off_led();
                        have_timer_work = false;
                    }
                    else
                    {
                        Serial.println("turn on led");
                        //turn_on_led();
                        have_timer_work = true;
                        break; // thoát khỏi vòng lặp for
                    }        
                }  
                else
                {
                    Serial.printf("Alarm %d is on but not true time \r\n",i);
                    have_timer_work = false;
                }
              
            }   
            else
            {
                Serial.printf("Alarm %d is off \r\n",i);
                
            }   
        }
        /// xuống đây

        if (have_timer_work == true)
        {
            turn_on_led();
        }
        else
        {
            turn_off_led();
        }
        


    }
    
}