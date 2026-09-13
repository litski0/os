#include "idt.h"
#include "io.h"
#include "framebuffer.h"
#include "serial.h"
#include "gdt.h"
#include "string.h"

char keyboard_us[IDT_MAX_CHAR_KEYBOARD]; 

extern uint32_t interrupt_handler_array[];


struct idt_entry idt_entries[IDT_MAX_INTERRUPTS];
struct idt_ptr ip;




void keyboard_init(){

    keyboard_us[0x2]='1';
    keyboard_us[0x3]='2';
    keyboard_us[0x4]='3';
    keyboard_us[0x5]='4';
    keyboard_us[0x6]='5';
    keyboard_us[0x7]='6';
    keyboard_us[0x8]='7';
    keyboard_us[0x9]='8';
    keyboard_us[0xA]='9';
    keyboard_us[0xB]='0';

    keyboard_us[0x10]='q';
    keyboard_us[0x11]='w';
    keyboard_us[0x12]='e';
    keyboard_us[0x13]='r';
    keyboard_us[0x14]='t';
    keyboard_us[0x15]='y';
    keyboard_us[0x16]='u';
    keyboard_us[0x17]='i';
    keyboard_us[0x18]='o';
    keyboard_us[0x19]='p';

    keyboard_us[0x1E]='a';
    keyboard_us[0x1F]='s';
    keyboard_us[0x20]='d';
    keyboard_us[0x21]='f';
    keyboard_us[0x22]='g';
    keyboard_us[0x23]='h';
    keyboard_us[0x24]='j';
    keyboard_us[0x25]='k';
    keyboard_us[0x26]='l';


    keyboard_us[0x2C]='z';
    keyboard_us[0x2D]='x';
    keyboard_us[0x2E]='c';
    keyboard_us[0x2F]='v';
    keyboard_us[0x30]='b';
    keyboard_us[0x31]='n';
    keyboard_us[0x32]='m';

    keyboard_us[0x39]=' ';

    keyboard_us[0x1C]='\n';
    keyboard_us[0x0F]='\t';


}


char keyboard_handler(int s){

    
    return keyboard_us[s];
 
    
}


void idt_set_gate(uint8_t  num, uint32_t  base){
    idt_entries[num].off_low=(base&0xFFFF);
    idt_entries[num].off_high=((base>>16)&0xFFFF);
    idt_entries[num].zero=0;
    idt_entries[num].attr=IDT_ATTR_INTERRUPT; 
    idt_entries[num].seg_sel=GDT_KERNEL_CODE_SEG;
}

void init_idt(){
    for(int i=0;i<IDT_MAX_INTERRUPTS;i++){
        idt_set_gate(i,interrupt_handler_array[i]);
    }
    ip.limit=sizeof(idt_entries)-1;
    ip.base=(uint32_t)&idt_entries;
    load_idt((uint32_t)&ip);
    keyboard_init();
}


// TODO: Need to add all various handler 
void interrupt_handler(struct cpu_state cpu ,uint32_t  interrupt ,struct stack_state stack){
    (void)cpu;
    (void)stack;


// TODO: make it complete ascii compiatable
    if(interrupt==IDT_INT_KEYBOARD){
        uint8_t s= inb(IO_PORT_KEYBOARD);
        outb(PIC_MASTER_COMMAND,IDT_EOI);

        if (s & IDT_KEYBOARD_UP_MASK){
            return;
        }

        s=keyboard_us[((int)s)];
        uint8_t schar[2];
        schar[0]=s;
        schar[1]='\0';
        fb_write(schar);
        serial_write(schar,SERIAL_COM1_BASE);
        
    }
 
    return;
}



