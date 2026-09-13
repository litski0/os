#include "pic.h"

void pic_remap(void ){
    outb(PIC_MASTER_COMMAND, PIC_ICW1_INIT | PIC_ICW1_ICW4); // seting the initlaising parametre
    outb(PIC_SLAVE_COMMAND, PIC_ICW1_INIT | PIC_ICW1_ICW4);
    
    outb(PIC_MASTER_DATA, PIC_MASTER_OFFSET);  // seting theoffsets
    outb(PIC_SLAVE_DATA, PIC_SLAVE_OFFSET);
    
    outb(PIC_MASTER_DATA, 1 << PIC_CASCADE_IRQ);  //seting the ccascades idetinties
    outb(PIC_SLAVE_DATA, PIC_CASCADE_IRQ);
    
    outb(PIC_MASTER_DATA, PIC_ICW4_8086); // settign the 32 bit
    outb(PIC_SLAVE_DATA, PIC_ICW4_8086);

    outb(PIC_MASTER_DATA,0xFD); // only allowing keyboard
    outb(PIC_SLAVE_DATA, 0xFF);

}