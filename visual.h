#ifndef VISUAL_H
#define VISUAL_H

enum  {	BLACK = 0x0000, 
	BLUE = 0x1000, 
	GREEN = 0x2000, 
	WHITE = 0xF000, 
	PURPLE = 0x5000, 
	RED = 0x4000, 
	YELLOW = 0xE000   };



extern unsigned char kbdus[128];
extern unsigned short *video_out;
extern unsigned short font_color;

int cur_line();
void print(char *str);
void set_bg_color(unsigned short color);
void change_font_color(unsigned short color);

#endif
