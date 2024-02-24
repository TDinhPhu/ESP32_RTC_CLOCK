


#define NUMBER_OF_BUTTON            4

#define GPIO_BUTTON_1               19
#define GPIO_BUTTON_2               18
#define GPIO_BUTTON_3               4
#define GPIO_BUTTON_4               23



#define BUTTON_UP      0
#define BUTTON_DOWN    1
#define BUTTON_ENTER   2
#define BUTTON_EXIT    3




typedef struct
{
	bool status;
    uint32_t counter_press;
}BUTTON_INFO;


typedef struct
{
	String name;
    uint8_t age;
    float math;
}STUDENT_INFO;

void init_button();
void read_button();