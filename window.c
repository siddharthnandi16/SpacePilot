#include <windows.h>
void syncConsoleBufferToWindow() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);

    // Visible window dimensions (not buffer dimensions)
    int windowWidth  = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int windowHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    COORD newSize;
    newSize.X = windowWidth;
    newSize.Y = windowHeight;

    SetConsoleScreenBufferSize(hOut, newSize);
}