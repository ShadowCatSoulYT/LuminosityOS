#include "../system/fs.h"

void print(const char* str) {
    unsigned short* video_memory = (unsigned short*)0xB8000;

    for (int i = 0; str[i] != '\0'; ++i) {
        video_memory[i] = (video_memory[i] & 0xFF00) | str[i];
    }
}

void kernel_main() {
    init_system();
    print("Welcome to LuminosityOS!");
    while(1) {
    }
}  
