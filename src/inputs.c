#include "inputs.h"
#include <unistd.h>

int editor_read_key()
{
  char c;

  while (read(STDIN_FILENO, &c, 1) != 1)
    ;

  /* ENTER normalize */
  if (c == '\r' || c == '\n')
    return KEY_ENTER;

  /* ESC sequence */
  if (c == '\x1b')
  {

    char seq[2];

    if (read(STDIN_FILENO, &seq[0], 1) != 1)
      return '\x1b';

    if (read(STDIN_FILENO, &seq[1], 1) != 1)
      return '\x1b';

    if (seq[0] == '[')
    {
      switch (seq[1])
      {
      case 'A':
        return KEY_ARROW_UP;
      case 'B':
        return KEY_ARROW_DOWN;
      case 'C':
        return KEY_ARROW_RIGHT;
      case 'D':
        return KEY_ARROW_LEFT;
      }
    }

    return KEY_NULL;
  }

  return c;
}

int is_printable_ascii(char c)
{
  return (c >= 32 && c <= 126);
}
