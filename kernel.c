unsigned short *video_out = (unsigned short *)0xb8000;

void print(char *str)
{
	while (*str != '\0')
		*video_out++ = 0x5200 | *str++;
}

void kernelMain()
{
	print("It's now in C");
	print(" and looks acid!");

	while(1);
}
