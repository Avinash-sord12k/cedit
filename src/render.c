#include "render.h"
#include "terminal.h"
#include "status.h"

#include <unistd.h>

void refresh_screen(EditorState *E)
{
  clrscr();

  // file content draw
  write(STDOUT_FILENO, E->buffer, E->len);

  // status bar draw
  draw_status_bar(E);

  // cursor wapas text area me
  move_cursor(E->cursor_x, E->cursor_y);
}

void editor_index_to_xy(EditorState *E, int *x, int *y)
{
  int cx = 0;
  int cy = 0;

  for (int i = 0; i < E->cursor_index; i++)
  {

    if (E->buffer[i] == '\n')
    {
      cy++;
      cx = 0;
    }
    else
    {
      cx++;
    }
  }

  *x = cx;
  *y = cy;
}
