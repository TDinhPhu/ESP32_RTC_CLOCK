#include <Arduino.h>
#include "module_LED.h"
#include "module_button.h"

extern BUTTON_INFO button_info[NUMBER_OF_BUTTON];

int list_gpio_led[NUMBER_OF_LED] = {GPIO_LED_GREEN,GPIO_LED_YELLOW,GPIO_LED_RED};
bool list_status_led[NUMBER_OF_LED] = {0};


void init_led()
{    
  for (size_t i = 0; i < NUMBER_OF_LED; i++)
  {
      pinMode(list_gpio_led[i], OUTPUT);
  }
}


void control_led()
{
    for (size_t i = 0; i < NUMBER_OF_LED; i++)
    {
        if (button_info[i].status == true)
        {
            button_info[i].status = false;
            if (list_status_led[i] == true)
            {
                Serial.printf("Tắt led : %d \r\n",i+1);
                list_status_led[i] = false;
                digitalWrite(list_gpio_led[i], LOW);
            }
            else
            {
                Serial.printf("Bật led : %d \r\n",i+1);
                list_status_led[i] = true;
                digitalWrite(list_gpio_led[i], HIGH);
            }           
        }        
    }   

}