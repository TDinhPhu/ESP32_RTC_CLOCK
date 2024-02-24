
#define SCREEN_DISPLAY_TIME          0
#define SCREEN_MENU                  1
#define SCREEN_SET_TIME              2
#define SCREEN_SET_DATE              3
#define SCREEN_SET_ALARM             4


#define CHOOSE_SET_TIME              0
#define CHOOSE_SET_ALARM             1


#define TYPE_SETTING_HOUR            0
#define TYPE_SETTING_MIN             1
#define TYPE_SETTING_SEC             2

#define TYPE_SETTING_DAY             3
#define TYPE_SETTING_MONTH           4
#define TYPE_SETTING_YEAR            5
#define TYPE_SETTING_DAY_OF_WEEK     12


#define TYPE_SETTING_NUMBER_ALARM          6
#define TYPE_SETTING_ONOFF_ALARM           7
#define TYPE_SETTING_HOUR_START_ALARM      8
#define TYPE_SETTING_MIN_START_ALARM       9
#define TYPE_SETTING_HOUR_STOP_ALARM       10
#define TYPE_SETTING_MIN_STOP_ALARM        11



void init_lcd();
void display_number();
void display_error_init_rtc();
void display_error_rtc_not_runing();
void display_time(uint8_t col, uint8_t row,uint8_t hour, uint8_t min, uint8_t sec);
void display_date(uint8_t col, uint8_t row, uint8_t dayOfTheWeek, uint8_t day, uint8_t mon, uint16_t year);
void display_system();
void clear_lcd();
void display_tick(uint8_t index);
void display_number(uint32_t col,uint32_t row,uint32_t number,bool blynk);
void change_value(int8_t type_change);
void check_time_return_main_screen();
void clear_time_return_main_screen();