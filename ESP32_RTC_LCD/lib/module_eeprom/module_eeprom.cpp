#include <EEPROM.h>
#include "module_eeprom.h"

uint8_t number_of_reset = 0;

void init_EEPROM()
{
    EEPROM.begin(EEPROM_SIZE);
}

void read_number_of_reset()
{
    number_of_reset = EEPROM.read(0);
    number_of_reset++;
    Serial.printf("number_of_reset : %d \r\n",number_of_reset);
    write_number_of_reset();
}

void write_number_of_reset()
{
    EEPROM.write(0, number_of_reset);
    EEPROM.commit();
}



void read_data_from_eeprom(uint32_t addr,char* data,uint32_t len)
{
    // ví dụ : 10    5 phần tử
    // 10 11 12 14 14
    for (uint32_t i = 0; i < len; i++)
    {
        data[i] = EEPROM.read(addr+i);
    }    
}

void write_data_to_eeprom(uint32_t addr,char* data,uint32_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        EEPROM.write(addr+i, data[i]);
        EEPROM.commit();
    }  

}