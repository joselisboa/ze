//
// Ze Console
//
// description: Console class for Windows
// author: José Vieira Lisboa
// url: https://github.com/joselisboa/ze
//
#ifndef _ZE_H_
#define _ZE_H_

#include <windows.h>
#include <string>

using namespace std;

typedef struct _dim {
    union dimension
    {
        int width;
        int height;
    };
} DIM;

typedef struct _dim2 {
    int width;
    int height;
} DIM2;

typedef struct _dim3 {
    int width;
    int height;
    int depth;
} DIM3;

class Ze
{
private:
    HANDLE _input_handle;
    HANDLE _output_handle;

public:
    WORD BLACK = 0;
    WORD BLUE_FADE = FOREGROUND_BLUE;
    WORD GREEN_FADE = FOREGROUND_GREEN;
    WORD CYAN_FADE = FOREGROUND_GREEN | FOREGROUND_BLUE;
    WORD RED_FADE = FOREGROUND_RED;
    WORD MAGENTA_FADE = FOREGROUND_RED | FOREGROUND_BLUE;
    WORD YELLOW_FADE = FOREGROUND_RED | FOREGROUND_GREEN;
    WORD WHITE_FADE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    WORD GRAY = FOREGROUND_INTENSITY;
    WORD BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE;
    WORD GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
    WORD CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE;
    WORD RED = FOREGROUND_INTENSITY | FOREGROUND_RED;
    WORD MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE;
    WORD YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
    WORD WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    DWORD info;
    INPUT_RECORD input_record;
    CONSOLE_CURSOR_INFO cursor_info;
    CONSOLE_SCREEN_BUFFER_INFO screen_info;
    WORD textColor();
    BOOL textColor(WORD color) { return SetConsoleTextAttribute(_output_handle, color); }
    BOOL resetTextColor() { return SetConsoleTextAttribute(_output_handle, WHITE_FADE); }   
    Ze &foreground(WORD);
    Ze &background(WORD);
    Ze &paintString(string, COORD, WORD);
    Ze &showCursor(bool bVisible = true);
    Ze &hideCursor(bool bVisible = false) { showCursor(bVisible); return *this; }
    Ze &cursorSize(const int dwSize = 0);
    Ze &cursorPosition(short x, short y) { cursorPosition(COORD{ x, y }); return *this; }
    Ze &cursorPosition(COORD pos) { SetConsoleCursorPosition(output(), pos); return *this; }
    Ze &textSize(int, int);
    Ze &screenSize(int, int);
    Ze &refresh();
    Ze &ch(char ch, COORD pos = { 0, 0 });
    Ze &cls(WORD);
    char ch();

    int cursorSize() { return cursor_info.dwSize; }
    Ze();

    //TODO remover estas funções
    HANDLE input() { return _input_handle; };
    HANDLE output() { return _output_handle; };
    Ze &_input();
};

#endif
