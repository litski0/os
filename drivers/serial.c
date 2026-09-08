#include "serial.h"
#include "io.h"

//TODO: Veriy Gemini thinks this would be error since we are not doing this by sending HIGH AND LOW byte
void serial_configure_baud_rate(unsigned int com, unsigned short divisor){
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB );
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}


void serial_configure_line(unsigned int com){
    //      * Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
    //      * Content: | d | b | prty  | s | dl  |
    //      * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
    outb(SERIAL_LINE_COMMAND_PORT(com),0x03); //sending data with 8bit 0parity bit and 1 stop bit and break control disabled
}

void serial_configure_buffer(unsigned int com){
    // Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
    // Content: | lvl | bs | r | dma | clt | clr | e |
    //  0xC7= 11000111
    outb(SERIAL_FIFO_COMMAND_PORT(com),0xC7);
}

void serial_configure_modem(unsigned int com){
    // Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
    // Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
    // only sending data therefore 0x03=00000011
    outb(SERIAL_MODEM_COMMAND_PORT(com),0x03);
}

int serial_is_empty(unsigned int com){
        //  * Bit:     | 7  | 6     |  5    | 4   |  3  | 2  | 1  | 0  |
        //  * Content: | IE | TEMPT | THRE  | BI  | FE  | PE | OE | DR | <- Transmission buffer empty
        //  * Value:   | 0 |    0   |   1   |  0  |  0  | 0  |  0 |  0 | = 0x20
    return (inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20 );
}

int serial_have_data(unsigned int com){
        //  * Bit:     | 7  | 6     |  5    | 4   |  3  | 2  | 1  | 0  |
        //  * Content: | IE | TEMPT | THRE  | BI  | FE  | PE | OE | DR | <- Data Ready
        //  * Value:   | 0 |    0   |   0   |  0  |  0  | 0  |  0 |  1 | = 0x01
    return (inb(SERIAL_LINE_STATUS_PORT(com)) & 1 );
}


//TODO: return amount of data read , currently only returns sucess exec 

int serial_read(unsigned int com, char*s){
    int index =0;
    while(index<SERIAL_MAX_READ_BUFF-1){
        if(serial_have_data(com)){
            s[index]=inb(com);
            if(s[index]=='\n' || s[index]=='\r'){
                s[index]='\0';
                break;
            }
            index++;
        
        }
    }
    s[index]='\0';
    return 0;
}



// TODO check if serial is faulty or not;
int serial_is_faulty(unsigned int com){
    (void)com; // remove this , just to supress werror wall
    return 0;
}

void serial_config_all(unsigned int com, unsigned short divisor){
    serial_configure_baud_rate(com,divisor);
    serial_configure_line(com);
    serial_configure_buffer(com);
    serial_configure_modem(com);

}

// TODO return the characters written, currently returns succesfull exec
int serial_write(char* s, int len,unsigned int com){
    int index=0;
    while(index<len){
        if(serial_is_empty(com)){
            outb(com,s[index]);
            index++;
        }
    }
    return 0;
}



