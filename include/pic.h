// Its vector offset. (ICW2)
// Tell it how it is wired to master/slaves. (ICW3)
// Gives additional information about the environment. (ICW4)

#include "io.h"
#include "typedef.h"

#ifndef INCLUDE_PIC_H
#define INCLUDE_PIC_H

#define PIC_MASTER 0x20
#define PIC_SLAVE 0xA0

#define PIC_MASTER_OFFSET 0x20
#define PIC_SLAVE_OFFSET 0x28

#define PIC_MASTER_COMMAND PIC_MASTER
#define PIC_MASTER_DATA (PIC_MASTER + 1)
#define PIC_SLAVE_COMMAND PIC_SLAVE
#define PIC_SLAVE_DATA (PIC_SLAVE + 1)

#define PIC_MASTER_SLAVE 0x04
#define CASCADE_IRQ 2

#define ICW1_ICW4	0x01	/* Indicates that ICW4 will be present */
#define ICW1_INIT	0x10		/* Initialization - required! */
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */

void PIC_remap(void);

#endif