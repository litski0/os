#include "io.h"
#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "serial.h"
#include "framebuffer.h"


int kmain(){
    init_gdt();
    init_idt();
    pic_remap();
    __asm__ volatile("sti");
    __asm__ volatile ("int 0x3");
    fb_write((uint8_t *)"This is AryL OS\nHello");
    serial_config_all(SERIAL_COM1_BASE,2);
    serial_write((uint8_t *)"This is AryL OS\nHello",SERIAL_COM1_BASE);
    return 0;
}

