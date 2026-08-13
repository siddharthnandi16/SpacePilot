/* This is a vertical scrolling bullet hell game that uses ASCII graphics. The gameplay is divded 
into stages. The player can move freely within the screen boundaries.
 During each stage the player faces many enemies who shoot bullets at them. There are two
minibosses and one final boss in each stage. 
Getting hit by a bullet causes the player to lose a life.
If all lives are lost, you get a game over and have to start over.
RED= ENEMY, YELLOW= BULLET, GREEN= PLAYER, BLUE=POWER-UPs
Planned additional features: Music, Power-Ups, unlockable upgrades, screen-clearing bombs,
 multiple playable characters with different abilities, sound effects, TTS Voice acting  */
#include <pdcurses.h>
#include <windows.h>
#include "titlescreen.h"
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
int main(){    
initscr();
curs_set(0);
noecho();
    /* HWND ConsoleWindow;
ConsoleWindow = GetConsoleWindow();
ShowWindow(ConsoleWindow, SW_MAXIMIZE); 
resize_term(0,0); 
touchwin(stdscr);
refresh(); */
// This was commented out because it froze the program. It is intended to maximise the window.
syncConsoleBufferToWindow();
resize_term(0,0);
touchwin(stdscr);
refresh();
// mvprintw(0, 0, "LINES=%d COLS=%d", LINES, COLS);
// mvprintw(10, 10, "TEST");
drawTitleScreen();
refresh();
getch();
int max_x, max_y;
getmaxyx(stdscr, max_y, max_x);
    
    endwin();
    return 0;
}