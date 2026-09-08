#include "typedef.h"

#ifndef INCLUDE_IDT_H

#define INCLUDE_IDT_H

// "High"
// Bit:     | 31              16 | 15 | 14 13 | 12 | 11 | 10 9 8 | 7 6 5 | 4 3 2 1 0 |
// Content: | offset high        | P  | DPL   | 0  | D  | 1  1 0 | 0 0 0 | reserved  |

// "Low"
// Bit:     | 31              16 | 15              0 |
// Content: | segment selector   | offset low        |

struct idt_entry{
    uint16_t off_low;
    uint16_t seg_sel;
    uint8_t zero;
    uint8_t attr;
    uint16_t off_high;
    
}__attribute__((packed));


// same as gdt

struct idt_ptr{
    uint16_t limit;
    uint32_t base;

}__attribute__((packed));


// since using pushad its order is EAX, ECX, EDX, EBX, ESP , EBP, ESI, EDI.
struct cpu_state{
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;


}__attribute__((packed));


struct stack_state{
    uint32_t error_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
}__attribute__((packed));


extern void load_idt(uint32_t idt_ptr_address);
void init_idt();
void interrupt_handler(struct cpu_state cpu,uint32_t interrupt ,struct stack_state stack );

#endif