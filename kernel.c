void print(const char* str) {
    // Pointer to the start of VGA text memory
    unsigned short* video_memory = (unsigned short*)0xB8000;

    for (int i = 0; str[i] != '\0'; ++i) {
        // We keep the existing color/attribute (the top 8 bits)
        // and only change the character (the bottom 8 bits)
        video_memory[i] = (video_memory[i] & 0xFF00) | str[i];
    }
}

void kernel_main() {
    print("Hello from the Kernel!");
    while(1) {
        // Halt or loop forever
    }
}  
