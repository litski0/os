#include "typedef.h"

#ifndef SERIAL_INCLUDE_H

#define SERIAL_INCLUDE_H

#define SERIAL_COM1_BASE 0x3f8
#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base+2)
#define SERIAL_LINE_COMMAND_PORT(base) (base+3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base+4)
#define SERIAL_LINE_STATUS_PORT(base) (base+5)

#define SERIAL_LINE_ENABLE_DLAB 0x80
#define SERIAL_DEFAULT_BAUDRATE_DIVISOR 2

#define SERIAL_MAX_READ_BUFF 512

void serial_configure_baud_rate(uint32_t   com, uint16_t divisor);
void serial_configure_line(uint32_t com);
void serial_configure_buffer(uint32_t com);
void serial_configure_modem(uint32_t com);
int serial_is_empty(uint32_t com);
int serial_have_data(uint32_t com);
int serial_read(uint32_t com, char*s);
int serial_is_faulty(uint32_t com);
void serial_config_all(uint32_t com, uint16_t divisor);
int serial_write(uint8_t* s,uint32_t com);



#endif