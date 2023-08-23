#ifdef _WIN32

#include "platform.h"

#include <windows.h>

void platform_out(int level, const char* message) {
    int colors[7] = {0x40, 0x04, 0x06, 0x07, 0x01, 0x08, 0x0C};

    HANDLE std_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(std_handle, colors[level]);

    SetConsoleOutputCP(CP_UTF8);

    WriteConsoleA(std_handle, message, strlen(message), 0, NULL);
}

#endif

