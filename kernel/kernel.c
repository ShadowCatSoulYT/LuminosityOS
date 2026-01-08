/* simple VGA text-mode printing for a freestanding kernel */
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static volatile unsigned short* const video_memory = (volatile unsigned short*)0xB8000;
static unsigned int cursor_pos = 0;            /* index in characters (0 .. 80*25-1) */
static unsigned char vga_attr = 0x0F;         /* attribute: 0x0F = white on black */

static inline unsigned short make_entry(char c, unsigned char attr) {
    return (unsigned short)attr << 8 | (unsigned char)c;
}

void clear_screen(void) {
    unsigned int total = VGA_WIDTH * VGA_HEIGHT;
    for (unsigned int i = 0; i < total; ++i) {
        video_memory[i] = make_entry(' ', vga_attr);
    }
    cursor_pos = 0;
}

static void scroll_if_needed(void) {
    unsigned int total = VGA_WIDTH * VGA_HEIGHT;
    if (cursor_pos < total) return;

    /* move each row up by one */
    for (unsigned int row = 0; row < VGA_HEIGHT - 1; ++row) {
        for (unsigned int col = 0; col < VGA_WIDTH; ++col) {
            video_memory[row * VGA_WIDTH + col] = video_memory[(row + 1) * VGA_WIDTH + col];
        }
    }
    /* clear last row */
    unsigned int last = (VGA_HEIGHT - 1) * VGA_WIDTH;
    for (unsigned int col = 0; col < VGA_WIDTH; ++col) {
        video_memory[last + col] = make_entry(' ', vga_attr);
    }
    cursor_pos = last;
}

void print(const char* str) {
    for (unsigned int i = 0; str[i] != '\0'; ++i) {
        char c = str[i];

        if (c == '\n') {
            /* move to start of next line */
            cursor_pos = ((cursor_pos / VGA_WIDTH) + 1) * VGA_WIDTH;
        } else {
            video_memory[cursor_pos] = make_entry(c, vga_attr);
            ++cursor_pos;
        }

        scroll_if_needed();
    }
}

void kernel_main(void) {
    clear_screen();
    print("Welcome to LuminosityOS!\nBoot sequence initialized.\n");
    while (1) { __asm__ volatile ("hlt"); } /* halt CPU until next interrupt */
}
