#include "status.h"
#include "terminal.h"

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void editor_set_status(EditorState *E, const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);

  vsnprintf(E->status_msg, sizeof(E->status_msg), fmt, ap);

  va_end(ap);

  E->status_time = time(NULL);
}

void draw_status_bar(EditorState *E)
{
  char left[256];
  char right[128];

  /* ----- LEFT SIDE (persistent info) ----- */
  snprintf(left, sizeof(left),
           " %s %s | chars:%d | ^S Save ^Q Quit ^C Copy ^Y Paste ",
           E->filename,
           E->dirty ? "*" : "",
           E->len);

  /* ----- RIGHT SIDE (temporary message) ----- */
  right[0] = '\0';

  if (E->status_msg[0] &&
      (time(NULL) - E->status_time <= 3))
  {
    snprintf(right, sizeof(right), "%s", E->status_msg);
  }

  int left_len = strlen(left);
  int right_len = strlen(right);

  /* never exceed screen width */
  if (left_len > E->cols)
    left_len = E->cols;

  if (right_len > E->cols)
    right_len = E->cols;

  write(STDOUT_FILENO, "\x1b[7m", 4); /* reverse color */

  move_cursor(0, E->rows - 1);

  /* draw left part */
  write(STDOUT_FILENO, left, left_len);

  /* fill middle space */
  int space = E->cols - left_len - right_len;
  if (space < 0)
    space = 0;

  for (int i = 0; i < space; i++)
    write(STDOUT_FILENO, " ", 1);

  /* draw right-aligned message */
  if (right_len > 0)
    write(STDOUT_FILENO, right, right_len);

  /* fill remaining (safety) */
  int used = left_len + space + right_len;
  for (int i = used; i < E->cols; i++)
    write(STDOUT_FILENO, " ", 1);

  write(STDOUT_FILENO, "\x1b[m", 3); /* reset style */
}
