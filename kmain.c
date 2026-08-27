#include "io.h"

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

#define FB_GREEN 2
#define FB_DARK_GREY 8

#define FB_WHITE 15
#define FB_BLACK 0

#define FB_MAX_COL 80
#define FB_MAX_ROW 25

#define FB_MAX_CELL (FB_MAX_COL*FB_MAX_ROW)

#define FB_TAB 4


#define SERIAL_COM1_BASE 0x3f8
#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base+2)
#define SERIAL_LINE_COMMAND_PORT(base) (base+3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base+4)
#define SERIAL_LINE_STATUS_PORT(base) (base+5)

#define SERIAL_LINE_ENABLE_DLAB 0x80
#define SERIAL_DEFAULT_BAUDRATE_DIVISOR 2

#define SERIAL_MAX_READ_BUFF 512


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




int FB_LAST_CUR=0;


char* fb = (char *)(0x000B8000);

void fb_write_cell(unsigned int i,char c, unsigned char fg, unsigned char bg){
    // one character takes 2 indices, therefore the nex tshould come after 2 ; therefore i should be i*2;
    int next_char_pos=i*2;
    fb[next_char_pos]=c;
    fb[next_char_pos+1]=((bg&0x0F)<<4)|(fg&0x0F);
}

void fb_move_cursor(unsigned short pos){
    outb(FB_COMMAND_PORT,FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,((pos>>8)&0x00FF));
    outb(FB_COMMAND_PORT,FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,pos&0x00FF);
}


//TODO: should return the amount of chars displayed
// Currently return succes or not
int fb_write(char * buf, unsigned int len){
        // get last position of cursor if null then i will start typing from the frist of the screen 
        
        int curr_pos=FB_LAST_CUR;
      
        for(unsigned int i =0;i<len;i++){
            if(buf[i]=='\n'){
                curr_pos+=FB_MAX_COL-(curr_pos%FB_MAX_COL);
                continue;
            }
            else if(buf[i]=='\t'){
                curr_pos+=FB_TAB;
                continue;
            }
        
            curr_pos=(curr_pos)%(FB_MAX_CELL);
            fb_write_cell(curr_pos,buf[i],FB_WHITE,FB_BLACK);
            fb_move_cursor(curr_pos);
            curr_pos++;
            
        }
        FB_LAST_CUR=curr_pos;
        return 0;
    
        
}  

int kmain(){
    fb_write("This is AryL OS\nHello",21);
    serial_config_all(SERIAL_COM1_BASE,2);
    serial_write("This is AryL OS\nHello",21,SERIAL_COM1_BASE);
    return 0;
}

