#ifndef INCLUDE_GDT_H

#define INCLUDE_GDT_H

//Descriptor
// * Byte:    | 7        | 6          | 5      | 4          |3      2| 1       0|
// * Content: | baseHigh | granualrity| access | baseMiddle |baseLow | limitLow | 


//Granuality
// * Bit        |7|6  |5|4  |3     0|
// * Content    |G|D/B|L|AVL| Limit |

// G: Set to multiply Limit by 4KB
// D/B: 0-16 bit 1-32 bit Protected;
// L: 0-32 bit 1-64 bit Long Mode 
//AVL: could be used by me 
//Limit: the top 4 bits of segment limit

// Access
// * Bit        |7|6  5|4|3 |2 |1 | 0|
// * Content    |P| DPL|S|EX|DC|RW|AC|

// P= Present 1
// DPL= Privellege 00
// S = Type for CODE/DATA 1 , 0 : for system segment
// EX=1 :Code 0: Data
// RW=1(Read or Write) : Code(Read) , 1: Data (Write)
// AC: Srt by CPU when it access 

void init_gdt();
void gdt_set_gate(int num ,unsigned int base, unsigned int limit, char access, char gran);


struct gdt_entry{
    unsigned short limit_low;
    unsigned short base_low;
    char base_middle;
    char access;
    char granualrity;
    char base_high;
} __attribute__((packed));


struct gdt_ptr{
    unsigned short limit;
    unsigned int base;

} __attribute__((packed));

extern void load_gdt(unsigned int gdt_ptr_address);



#endif