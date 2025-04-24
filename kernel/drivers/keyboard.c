// OceanOS
// Kernel Drivers
#include "keyboard.h"
#include "display.h"
#include "io.h"

#define BUFFER_SIZE 128
static char input_buffer[BUFFER_SIZE];
static int buffer_index = 0;

static const char keymap[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`', 0,'\\',
    'z','x','c','v','b','n','m',',','.','/', 0,'*', 0,' ',
    // ...
};

static int shift_pressed = 0;

// 간단한 한글 조합기용
static char cho[] = "ㄱㄲㄴㄷㄸㄹㅁㅂㅃㅅㅆㅇㅈㅉㅊㅋㅌㅍㅎ";
static char jung[] = "ㅏㅐㅑㅒㅓㅔㅕㅖㅗㅛㅜㅠㅡㅣ";
static char jong[] = "ㄱㄲㄳㄴㄵㄶㄷㄹㄺㄻㄼㄽㄾㄿㅀㅁㅂㅄㅅㅆㅇㅈㅊㅋㅌㅍㅎ";
static char* hangul_stage[3] = { 0, 0, 0 }; // 초성, 중성, 종성

static uint8_t inb_kbd() {
    return inb(0x60);
}

void handle_keypress(uint8_t scancode) {
    if (scancode & 0x80) return; // key released

    char c = keymap[scancode];
    if (!c) return;

    if (buffer_index < BUFFER_SIZE - 1) {
        input_buffer[buffer_index++] = c;
        put_char(c);
    }
}

// 문자 하나 읽기
char getchar() {
    buffer_index = 0;
    while (1) {
        uint8_t sc = inb_kbd();
        handle_keypress(sc);
        if (sc == 0x1C) { // Enter
            input_buffer[buffer_index] = '\0';
            return '\n';
        }
    }
}

// 한 줄 입력
void getline(char* buf, int maxlen) {
    buffer_index = 0;
    while (1) {
        uint8_t sc = inb_kbd();
        if (sc == 0x1C) { // Enter
            input_buffer[buffer_index] = '\0';
            for (int i = 0; i < buffer_index && i < maxlen - 1; i++)
                buf[i] = input_buffer[i];
            buf[buffer_index] = '\0';
            put_char('\n');
            return;
        } else {
            handle_keypress(sc);
        }
    }
}

// 아직 한글 조합은 안 넣음. 조합기 추가할 수 있음.
void init_keyboard() {
    // PIC 등 설정 가능
}
