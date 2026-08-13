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
int main(){
    
initscr();
    nodelay(stdscr, TRUE);
    HWND ConsoleWindow;
ConsoleWindow = GetConsoleWindow();
ShowWindow(ConsoleWindow, SW_MAXIMIZE);
    resize_term(0,0);
    //napms(10000); 
    // Debug only line
    endwin();
    return 0;
}