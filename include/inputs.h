#ifndef INPUT_H
#define INPUT_H

enum EditorKey
{
  KEY_NULL = 0,

  KEY_CTRL_A = 1,
  KEY_CTRL_C = 3,
  KEY_CTRL_E = 5,
  KEY_CTRL_Q = 17,
  KEY_CTRL_S = 19,
  KEY_CTRL_U = 21,
  KEY_CTRL_Y = 25,

  KEY_ENTER = 10,
  KEY_BACKSPACE = 127,

  KEY_ARROW_LEFT = 1000,
  KEY_ARROW_RIGHT = 1001,
  KEY_ARROW_UP = 1002,
  KEY_ARROW_DOWN = 1003,
};

int is_printable_ascii(char c);
int editor_read_key();

#endif