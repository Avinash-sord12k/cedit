#include "terminal.h"

#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void move_cursor(int x, int y)
{
  char buf[32];
  snprintf(buf, sizeof(buf), "\x1b[%d;%dH", y + 1, x + 1);
  write(STDOUT_FILENO, buf, strlen(buf));
}

void get_window_size(EditorState *E)
{
  struct winsize ws;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
  E->rows = ws.ws_row;
  E->cols = ws.ws_col;
}

void clrscr()
{
  write(STDOUT_FILENO, "\x1b[2J\x1b[H", 7); // clear screen
}

void disable_raw()
{
  if (GLOBAL_E)
  {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &GLOBAL_E->orig);
  }
  else
  {
    perror("GLOBAL_E is NULL");
    exit(1);
  }
}

void enable_raw(EditorState *E)
{
  if (tcgetattr(STDIN_FILENO, &E->orig) == -1)
    exit(1);
  atexit(disable_raw);

  struct termios raw = E->orig;
  raw.c_lflag &= ~(ECHO | ICANON | ISIG);
  raw.c_iflag &= ~(IXON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
