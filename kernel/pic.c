#include "pic.h"

void PIC_remap(void ){
    outb(PIC_MASTER_COMMAND, ICW1_INIT | ICW1_ICW4); // seting the initlaising parametre
    outb(PIC_SLAVE_COMMAND, ICW1_INIT | ICW1_ICW4);
    
    outb(PIC_MASTER_DATA, PIC_MASTER_OFFSET);  // seting theoffsets
    outb(PIC_SLAVE_DATA, PIC_SLAVE_OFFSET);
    
    outb(PIC_MASTER_DATA, 1 << CASCADE_IRQ);  //seting the ccascades idetinties
    outb(PIC_SLAVE_DATA, CASCADE_IRQ);
    
    outb(PIC_MASTER_DATA, ICW4_8086); // settign the 32 bit
    outb(PIC_SLAVE_DATA, ICW4_8086);

    outb(PIC_MASTER_DATA,0xFD); // only allowing keyboard
    outb(PIC_SLAVE_DATA, 0xFF);

}