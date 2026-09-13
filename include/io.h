#include "typedef.h"
#ifndef IO_INCLUDE_H
#define IO_INCLUDE_H

#define IO_PORT_KEYBOARD 0x60
#define IO_PORT_PIC 0x20


extern void  outb(uint16_t port, uint8_t data);
extern uint8_t inb(uint16_t port);



#endif