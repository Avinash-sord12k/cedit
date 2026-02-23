#ifndef TERMINAL_H
#define TERMINAL_H

#include "editor.h"
#include <termios.h>

void get_window_size(EditorState *E);
void disable_raw();
void enable_raw(EditorState *E);
void clrscr();
void move_cursor(int x, int y);

#endif