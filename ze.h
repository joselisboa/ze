#ifndef _ZE_H_
#define _ZE_H_
#include "windows.h"

class Ze
{
private:
    HANDLE _out;
    CONSOLE_CURSOR_INFO _cci;

public:
    void show_console_cursor(bool bVisible);
    void cursor_size(const int dwSize = 0);
    int cursor_size() const;
    Ze() { _out = GetStdHandle(STD_OUTPUT_HANDLE); }
};

#endif
