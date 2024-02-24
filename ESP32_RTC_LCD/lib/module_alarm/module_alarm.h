#include <Arduino.h>

#define NUMBER_OF_ALARM          10
#define LEN_BUFFER_ALARM_INFO    204

typedef struct
{
	uint32_t status;
    uint32_t hour_start;
    uint32_t min_start;
    uint32_t hour_stop;
    uint32_t min_stop;
}ALARM_t; // 20bytes

typedef union
{
    struct
    {
        ALARM_t alarm[NUMBER_OF_ALARM];
        uint32_t current_alarm;
    }data;
    char buffer_alarm_info[LEN_BUFFER_ALARM_INFO];
}ALARM_INFO_t;



void write_alarm_info_to_eeprom();
void read_alarm_info_from_eeprom();

// typedef struct
// {
//     uint32_t namsinh; // 4bytes
//     uint32_t tuoi;    // 4bytes

// } data;




// typedef union
// {
//     struct
//     {
//         uint32_t namsinh;
//         uint32_t tuoi;   
//         uint16_t lop;
//     } data;
//     char buffer_data[10];  // 8bytes  -   0 1 2 3 4 5 6 7
// } data_t;

