// OceanOS
// Kernel Drivers
// display.c
#include "display.h"

static int cursor_row = 0;
static int cursor_col = 0;
static uint8_t default_color = 0x0F; // White on black

void set_cursor(int row, int col) {
    cursor_row = row;
    cursor_col = col;
    uint16_t pos = row * VGA_WIDTH + col;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void clear_screen() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            VIDEO_MEMORY[y * VGA_WIDTH + x] = (default_color << 8) | ' ';
        }
    }
    set_cursor(0, 0);
}

void put_char(char c) {
    if (c == '\n') {
        cursor_row++;
        cursor_col = 0;
    } else {
        VIDEO_MEMORY[cursor_row * VGA_WIDTH + cursor_col] = (default_color << 8) | c;
        cursor_col++;
        if (cursor_col >= VGA_WIDTH) {
            cursor_col = 0;
            cursor_row++;
        }
    }

    if (cursor_row >= VGA_HEIGHT) {
        clear_screen();  // Scroll 대신 간단하게 clear
    }

    set_cursor(cursor_row, cursor_col);
}

void print(const char* str) {
    while (*str) {
        put_char(*str++);
    }
}

void print_at(const char* str, int row, int col) {
    set_cursor(row, col);
    print(str);
}
