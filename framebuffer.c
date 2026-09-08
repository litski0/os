#include "framebuffer.h"
#include "io.h"

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