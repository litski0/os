// Its vector offset. (ICW2)
// Tell it how it is wired to master/slaves. (ICW3)
// Gives additional information about the environment. (ICW4)

#include "io.h"
#include "typedef.h"

#ifndef PIC_INCLUDE_H
#define PIC_INCLUDE_H

#define PIC_MASTER (IO_PORT_PIC)
#define PIC_SLAVE 0xA0

#define PIC_MASTER_OFFSET 0x20
#define PIC_SLAVE_OFFSET 0x28

#define PIC_MASTER_COMMAND PIC_MASTER
#define PIC_MASTER_DATA (PIC_MASTER + 1)
#define PIC_SLAVE_COMMAND PIC_SLAVE
#define PIC_SLAVE_DATA (PIC_SLAVE + 1)

#define PIC_MASTER_SLAVE 0x04
#define PIC_CASCADE_IRQ 2

#define PIC_ICW1_ICW4	0x01	/* Indicates that ICW4 will be present */
#define PIC_ICW1_INIT	0x10		/* Initialization - required! */
#define PIC_ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */



//TODO implement all irqs

// PIC 1	Hardware	PIC 2	Hardware
// 0	Timer	8	Real Time Clock
// 1	Keyboard	9	General I/O
// 2	PIC 2	10	General I/O
// 3	COM 2	11	General I/O
// 4	COM 1	12	General I/O
// 5	LPT 2	13	Coprocessor
// 6	Floppy disk	14	IDE Bus
// 7	LPT 1	15	IDE Bus

#define PIC_IRQ_TIMER 0
#define PIC_IRQ_KEYBOARD 1


void pic_remap(void);

#endif