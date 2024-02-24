
void init_EEPROM();

#define EEPROM_SIZE      256  //256 BYTES

void read_number_of_reset();
void write_number_of_reset();
void read_data_from_eeprom(uint32_t addr,char* data,uint32_t len);
void write_data_to_eeprom(uint32_t addr,char* data,uint32_t len);