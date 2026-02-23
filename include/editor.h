#ifndef EDITOR_H
#define EDITOR_H

#include <stdint.h>
#include <termios.h>
#include <time.h>

typedef struct
{
  /* terminal */
  struct termios orig;
  int rows;
  int cols;

  char *buffer;
  int len;
  int capacity;

  int cursor_x;
  int cursor_y;
  int cursor_index;

  char clipboard[1024];
  int clipboard_len;

  char *filename;
  int dirty;            // file modified?
  char status_msg[128]; // temporary message
  time_t status_time;   // message timestamp

} EditorState;

extern EditorState *GLOBAL_E;

void editor_init(EditorState *E);

#endif