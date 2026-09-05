#include "gdt.h"


struct gdt_entry gdt[3];
struct gdt_ptr gp;

void gdt_set_gate(int num ,unsigned int base, unsigned int limit, char access, char gran){
    gdt[num].base_low=(base & 0xFFFF);
    gdt[num].base_middle=((base >> 16) & 0xFF);
    gdt[num].base_high=((base >> 24) & 0xFF);
    gdt[num].limit_low=(limit & 0xFFFF);
    gdt[num].granualrity=((limit >> 16)& 0xF) | (gran&0xF0);
    gdt[num].access=access;


}

void init_gdt(){
    gp.limit=(sizeof(struct gdt_entry)*3) - 1;
    gp.base = (unsigned int)&gdt;

    gdt_set_gate(0,0,0,0,0); //Null
    gdt_set_gate(1,0,0xFFFFFFFF,0x9A,0xCF); // kernel code seg
    gdt_set_gate(2,0,0xFFFFFFFF,0x92,0xCF); // kernel data seg
    load_gdt((unsigned int)&gp);

}