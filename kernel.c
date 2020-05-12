#define VGA_MEM (unsigned short *)0xb8000

enum Color 
     {	BLACK = 0x0000, 
	BLUE = 0x1000, 
	GREEN = 0x2000, 
	WHITE = 0xF000, 
	PURPLE = 0x5000, 
	RED = 0x4000, 
	YELLOW = 0xE000   };

unsigned short *video_out = VGA_MEM;
unsigned short font_color = GREEN / 16;

int cur_line()
{
	return (video_out - VGA_MEM) / 80 + 1;	
}

void print(char *str)
{
	while (*str != '\0') {
		if (*str == '\n')
			video_out = VGA_MEM + 80 *  cur_line(); 
		else
			*video_out++ = *video_out | font_color | *str;
		str++;
	}
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

void kernelMain()
{
	set_bg_color(PURPLE);
	print("It's now in C");
	print(" and looks acid!");
	print("Let's check out\nHow new\nlines work");
	while(1);
}
