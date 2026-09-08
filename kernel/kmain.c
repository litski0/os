#include "io.h"
#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "serial.h"
#include "framebuffer.h"


int kmain(){
    init_gdt();
    init_idt();
    PIC_remap();
    __asm__ volatile("sti");
    __asm__ volatile ("int 0x3");
    fb_write("This is AryL OS\nHello",21);
    serial_config_all(SERIAL_COM1_BASE,2);
    serial_write("This is AryL OS\nHello",21,SERIAL_COM1_BASE);
    return 0;
}

