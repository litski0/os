#include "idt.h"
#include "io.h"
#include "framebuffer.h"

extern uint32_t interrupt_handler_array[];


// TODO: Add macro isntead of hardcoded numbers
struct idt_entry idt_entries[256];
struct idt_ptr ip;

void idt_set_gate(uint8_t num, uint32_t base){
    idt_entries[num].off_low=(base&0xFFFF);
    idt_entries[num].off_high=((base>>16)&0xFFFF);
    idt_entries[num].zero=0;
    idt_entries[num].attr=0x8E; 
    idt_entries[num].seg_sel=0x8;
}

void init_idt(){
    for(int i=0;i<256;i++){
        idt_set_gate(i,interrupt_handler_array[i]);
    }
    ip.limit=sizeof(idt_entries)-1;
    ip.base=(uint32_t)&idt_entries;
    load_idt((uint32_t)&ip);
}


// TODO: Need to add all various handler 
void interrupt_handler(struct cpu_state cpu ,uint32_t interrupt ,struct stack_state stack){
    (void)cpu;
    (void)stack;


// TODO: Remove the hotfix, add macros for interrupt  and remove numbers
    if(interrupt==33){
        char s= inb(0x60);
        outb(0x20,0x20);
        char *s1=&s;
        fb_write(s1,1);
    }
 


    return;
}
