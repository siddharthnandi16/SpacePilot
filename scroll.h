#ifndef SCROLL_H
#define SCROLL_H
#include <stdbool.h>
char bgchar(int max_x, int max_y);
bool should_draw_cell(int max_y, int max_x);
int scrollanddraw(void);
#endif