void print(char * str) {
        unsigned short * VideoMem = (unsigned short *)0xb8000;
        for (int i = 0; str[i] != '\0'; i++)
                VideoMem[i] = (VideoMem[i] & 0xFF00) | str[i];
}

extern "C" void kernelMain() {
        print("Welcome to weirdOS! It might do something soon...");

        while(1);
}
