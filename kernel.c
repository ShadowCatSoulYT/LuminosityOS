void put_pixel(int x, int y, unsigned char color) {
    unsigned char* vga = (unsigned char*)0xA0000;
    vga[y * 320 + x] = color;
}

void kernel_main() {
    // Fill screen with a clear red color (color 4 in standard VGA palette)
    // to verify graphics are working and the kernel is actually running.
    for (int y = 0; y < 200; y++) {
        for (int x = 0; x < 320; x++) {
            put_pixel(x, y, 4);
        }
    }
    
    // Draw a small white square in the center
    for (int y = 90; y < 110; y++) {
        for (int x = 150; x < 170; x++) {
            put_pixel(x, y, 15);
        }
    }
    
    while(1) {
        __asm__("hlt");
    }
}
