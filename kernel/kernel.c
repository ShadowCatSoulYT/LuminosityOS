#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void print(const char* s) {
    char* vga = (char*)0xB8000;
    int i = 0;

    while(s[i]) {
        vga[i*2] = s[i];   // character
        vga[i*2+1] = 0x0F; // color (white)
        i++;
    }
}

void kernel_main(void) {
    print("I will bust if this works");
    while (1) { __asm__ volatile ("hlt"); } /* halt CPU until next interrupt */
}
