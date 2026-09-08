#ifndef INCLUDE_SERIAL_H

#define INCLUDE_SERIAL_H

#define SERIAL_COM1_BASE 0x3f8
#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base+2)
#define SERIAL_LINE_COMMAND_PORT(base) (base+3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base+4)
#define SERIAL_LINE_STATUS_PORT(base) (base+5)

#define SERIAL_LINE_ENABLE_DLAB 0x80
#define SERIAL_DEFAULT_BAUDRATE_DIVISOR 2

#define SERIAL_MAX_READ_BUFF 512

void serial_configure_baud_rate(unsigned int com, unsigned short divisor);
void serial_configure_line(unsigned int com);
void serial_configure_buffer(unsigned int com);
void serial_configure_modem(unsigned int com);
int serial_is_empty(unsigned int com);
int serial_have_data(unsigned int com);
int serial_read(unsigned int com, char*s);
int serial_is_faulty(unsigned int com);
void serial_config_all(unsigned int com, unsigned short divisor);
int serial_write(char* s, int len,unsigned int com);



#endif