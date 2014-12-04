#include <windows.h>
#include "ze.h"

void Ze::show_console_cursor(bool bVisible)
{
    GetConsoleCursorInfo(_out, &_cci);
    _cci.bVisible = bVisible;// cursor visibility
    SetConsoleCursorInfo(_out, &_cci);
}

void Ze::cursor_size(const int dwSize)// dwSize: 1 to 99
{
    _cci.dwSize = dwSize;
    _cci.bVisible = true;
    SetConsoleCursorInfo(_out, &_cci);
}

int Ze::cursor_size() const
{
    return _cci.dwSize;
}
