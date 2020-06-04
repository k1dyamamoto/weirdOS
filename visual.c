#define VGA_MEM (unsigned short *)0xb8000
#include "system.h"

unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   15,		/* Left shif */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   15,				/* Right shift */
  '*',
    14,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};
unsigned short *video_out = VGA_MEM;
unsigned short color_arr[3] = {YELLOW, RED, PURPLE};
unsigned short font_color;
unsigned char cur_color = 0;
unsigned char shiftbit = 0;

int cur_line()
{
	return (video_out - VGA_MEM) / 80 + 1;	
}

void print(char *str)
{
	if (video_out < VGA_MEM) {
		video_out = VGA_MEM;
		return;
	}
	while (*str != '\0') {
		if (*str == '\n')
			video_out = VGA_MEM + 80 *  cur_line(); 
		else if (*str == '\b')
			*(--video_out) = *video_out | font_color | ' '; 
		else if (shiftbit && (*str >= 'a') && (*str <= 'z'))
			*video_out++ = *video_out | font_color | (*str - 32);	
		else	
			*video_out++ = *video_out | font_color | *str;
		str++;
	}
}

void putc(unsigned char c)
{
	if (video_out < VGA_MEM) {
		video_out = VGA_MEM;
		return;
	}
	if (c == '\n')
		video_out = VGA_MEM + 80 *  cur_line(); 
	else if (c == '\b')
		*(--video_out) = *video_out | font_color | ' ';
	else if (shiftbit && (c >= 'a') && (c <= 'z'))
		*video_out++ = *video_out | font_color | (c - 32);	
	else
		*video_out++ = *video_out | font_color | c;
}

unsigned char inportb (unsigned short _port)
{
	unsigned char rv;
    	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    	return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void set_bg_color(unsigned short color)
{
	video_out = VGA_MEM;
	for (int cnt = 0; cnt < 80 * 25; cnt++)
		*(video_out + cnt) = color;
}

void change_font_color(unsigned short color)
{
	font_color = color / 16;
}

void keyboard_handler(struct regs *r)
{
	unsigned char scancode, key;
    	scancode = inportb(0x60);
	if (scancode & 0x80) {
		if (kbdus[scancode & 0x7F] == 15)
			shiftbit = 0;
	} else {
		key = kbdus[scancode];
		if (key == 15)
			shiftbit = 1;
        	else if (key == 14)
			change_font_color(color_arr[cur_color = ((cur_color + 1) % 3)]);
		else
			putc(key);
    	}
}

void keyboard_install()
{
	irq_install_handler(1, keyboard_handler);
}


