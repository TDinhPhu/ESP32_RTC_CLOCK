
#define TIME_READ_RTC     1000

void init_rtc();
void read_RTC();
void set_date_time(char daysOfTheWeek, uint8_t hour, uint8_t min, uint8_t sec,uint8_t day, uint8_t month, uint16_t year);
void print_data_time();
void get_current_time_to_setting();