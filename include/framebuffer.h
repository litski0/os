#include "typedef.h"
#ifndef FRAMEBUFFER_INCLUDE_H

#define FRAMEBUFFER_INCLUDE_H

#define FB_STARTING_ADDR 0x000B8000

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


void fb_write_cell(uint32_t i,uint8_t c, uint8_t fg, uint8_t bg);
void fb_move_cursor(uint16_t pos);
int fb_write(uint8_t * buf);

#endif