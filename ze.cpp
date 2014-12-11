//
// Ze Console
//
// description: Console class for Windows
// author: José Vieira Lisboa
// url: https://github.com/joselisboa/ze
//
#include <iostream>
#include <windows.h>
#include <string>
#include "ze.h"

using namespace std;

Ze &Ze::showCursor(bool bVisible)
{
    GetConsoleCursorInfo(_output_handle, &cursor_info);
    cursor_info.bVisible = bVisible;// cursor visibility
    SetConsoleCursorInfo(_output_handle, &cursor_info);
    return *this;
}

Ze &Ze::cursorSize(const int dwSize)// dwSize: 1 to 99
{
    cursor_info.dwSize = dwSize;
    cursor_info.bVisible = true;
    SetConsoleCursorInfo(_output_handle, &cursor_info);
    return *this;
}

Ze &Ze::paintString(string text, COORD pos, WORD cor)
{
    WORD aux = textColor();

    SetConsoleTextAttribute(_output_handle, cor);
    SetConsoleCursorPosition(_output_handle, pos);
    cout << text;

    textColor(aux);

    return *this;
}

Ze &Ze::textSize(int x, int y)
{
    CONSOLE_FONT_INFOEX cfont;
    cfont.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(_output_handle, false, &cfont);
    cfont.dwFontSize.X = x;
    cfont.dwFontSize.Y = y;
    SetCurrentConsoleFontEx(_output_handle, false, &cfont);
    return *this;
}

WORD Ze::textColor()
{
    refresh();
    return screen_info.wAttributes;
}

Ze &Ze::foreground(WORD color)
{
    SetConsoleTextAttribute(_output_handle, color);
    return *this;
}

Ze &Ze::background(WORD color)
{
    foreground(color << 4);
    return *this;
}

Ze &Ze::screenSize(int width, int height) {
    SMALL_RECT DisplayArea;
    SetConsoleScreenBufferSize(_output_handle, COORD {width, height });
    DisplayArea.Top = 0;
    DisplayArea.Left = 0;
    DisplayArea.Bottom = height - 1;
    DisplayArea.Right = width - 1;
    SetConsoleWindowInfo(_output_handle, TRUE, &DisplayArea);
    //return refresh();
    return *this;
}

Ze &Ze::refresh()
{
    GetConsoleScreenBufferInfo(_output_handle, &screen_info);
    return *this;
}

Ze::Ze()
{
    _input_handle = GetStdHandle(STD_INPUT_HANDLE);
    _output_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    // perde-se controlo do input (?)
    //SetConsoleMode(_input_handle, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

    GetConsoleScreenBufferInfo(_output_handle, &screen_info);
}

char Ze::ch()
{
    char ch;

    // ler input da consola
    ReadConsoleInput(input(), &input_record, 1, &info);

    // evento do teclado
    if (input_record.EventType == KEY_EVENT && input_record.Event.KeyEvent.bKeyDown) {
        ch = (char) input_record.Event.KeyEvent.wVirtualKeyCode;
    }
    else ch = '\0';

    // limpar o buffer de input da consola
    FlushConsoleInputBuffer(input());
    return ch;
}

Ze &Ze::ch(char ch, COORD pos)
{
    cursorPosition(pos);
    cout << ch;
    return *this;
}

Ze &Ze::cls(WORD background)
{
    this->background(background);
    system("cls");
    return *this;
}

Ze &Ze::_input()
{
    // ler input da consola
    ReadConsoleInput(_input_handle, &input_record, 1, &info);
    cursorPosition(0, 0);

    // evento do rato
    if (input_record.EventType == MOUSE_EVENT) {
    COORD coord;
    coord.X = input_record.Event.MouseEvent.dwMousePosition.X;
    coord.Y = input_record.Event.MouseEvent.dwMousePosition.Y;
    switch (input_record.Event.MouseEvent.dwButtonState) {
    case FROM_LEFT_1ST_BUTTON_PRESSED:
    cout << "Mouse[" << coord.X << "," << coord.Y << "]";
    break;
    default:;
    cout << "DEFAULT[" << coord.X << "," << coord.Y << "]";
    }
    }

    // evento do teclado
    if (input_record.EventType == KEY_EVENT && input_record.Event.KeyEvent.bKeyDown) {
        switch (input_record.Event.KeyEvent.wVirtualKeyCode) {
        case VK_RIGHT:
            cout << "RIGHT";
            break;
        case VK_LEFT:
            cout << "LEFT";
            break;
        case VK_UP:
            cout << "UP";
            break;
        case VK_DOWN:
            cout << "DOWN";
            break;
        default:
            cout << (char)input_record.Event.KeyEvent.wVirtualKeyCode;
        }
        cout << " (" << input_record.Event.KeyEvent.wVirtualKeyCode << ")    ";
    }

    // limpar o buffer de input da consola
    FlushConsoleInputBuffer(_input_handle);

    // acorrentar ...
    return *this;
}
