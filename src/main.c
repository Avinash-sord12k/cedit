#include "buffer.h"
#include "editor.h"
#include "inputs.h"
#include "render.h"
#include "status.h"
#include "terminal.h"
#include "version.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

EditorState *GLOBAL_E = NULL;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Usage: %s <filename>", argv[0]);
    return 1;
  }

  if (argc == 2 &&
      (strcmp(argv[1], "--version") == 0 ||
       strcmp(argv[1], "-v") == 0))
  {
    printf("%s\n", CEDIT_VERSION);
    return 0;
  }

  EditorState E;
  GLOBAL_E = &E;

  editor_init(&E);
  E.filename = argv[1];
  E.capacity = 1024;
  E.buffer = malloc(E.capacity);

  if (!E.buffer)
  {
    perror("malloc");
    exit(1);
  }

  editor_open(&E);
  E.cursor_x = 0;
  E.cursor_y = 0;
  E.cursor_index = 0;

  enable_raw(&E);
  get_window_size(&E);

  refresh_screen(&E);

  while (1)
  {
    int key = editor_read_key();

    switch (key)
    {

    case KEY_CTRL_Q:
      clrscr();
      return 0;

    case KEY_CTRL_S:
      save_file(&E);
      break;

    case KEY_ENTER:
      insert_newline(&E);
      break;

    case KEY_BACKSPACE:
      delete_char(&E);
      break;

    case KEY_CTRL_C:
      copy_line(&E);
      break;

    case KEY_CTRL_Y:
      paste_clipboard(&E);
      break;

    case KEY_ARROW_LEFT:
      if (E.cursor_index > 0)
        E.cursor_index--;
      break;

    case KEY_ARROW_RIGHT:
      if (E.cursor_index < E.len)
        E.cursor_index++;
      break;

    default:
      if (is_printable_ascii(key))
        insert_char(&E, key);
    }

    editor_index_to_xy(&E, &E.cursor_x, &E.cursor_y);
    refresh_screen(&E);
  }

  return 0;
}