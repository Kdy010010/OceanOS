#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VIDEO_MEMORY (uint16_t*)0xB8000

void clear_screen();
void put_char(char c);
void print(const char* str);
void print_at(const char* str, int row, int col);
void set_cursor(int row, int col);

#endif
