#include <Arduino.h>
#include "module_alarm.h"
#include "module_eeprom.h"

ALARM_INFO_t alarm_info;  // Khai báo biến có tên là alarm_info với kiểu dữ liệu là  ALARM_INFO_t (struct tự định nghĩa)




void write_alarm_info_to_eeprom()
{
    write_data_to_eeprom(1,alarm_info.buffer_alarm_info,LEN_BUFFER_ALARM_INFO);
}

void read_alarm_info_from_eeprom()
{
    read_data_from_eeprom(1,alarm_info.buffer_alarm_info,LEN_BUFFER_ALARM_INFO);
}