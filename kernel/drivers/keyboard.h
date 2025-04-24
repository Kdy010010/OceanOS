#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

void init_keyboard();
char getchar();         // 한 문자 읽기
void getline(char* buf, int maxlen); // 한 줄 읽기

#endif
