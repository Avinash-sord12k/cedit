#include "buffer.h"
#include "status.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void ensure_capacity(EditorState *E, int needed)
{
  if (needed <= E->capacity)
    return;

  int new_cap = (E->capacity == 0) ? 1024 : E->capacity;

  while (new_cap < needed)
    new_cap *= 2;

  char *new_buf = realloc(E->buffer, new_cap);
  if (!new_buf)
  {
    write(STDOUT_FILENO, "Out of memory\n", 14);
    exit(1);
  }

  E->buffer = new_buf;
  E->capacity = new_cap;
}

void insert_char(EditorState *E, char c)
{
  ensure_capacity(E, E->len + 1);

  memmove(
      &E->buffer[E->cursor_index + 1],
      &E->buffer[E->cursor_index],
      E->len - E->cursor_index);

  E->buffer[E->cursor_index] = c;

  E->len++;
  E->cursor_index++;

  E->dirty = 1;
}

void insert_newline(EditorState *E)
{
  ensure_capacity(E, E->len + 1);

  memmove(
      &E->buffer[E->cursor_index + 1],
      &E->buffer[E->cursor_index],
      E->len - E->cursor_index);

  E->buffer[E->cursor_index] = '\n';

  E->len++;
  E->cursor_index++;

  E->dirty = 1;
}

void delete_char(EditorState *E)
{
  if (E->cursor_index == 0)
    return;

  int i = E->cursor_index - 1;

  memmove(
      &E->buffer[i],
      &E->buffer[i + 1],
      E->len - i - 1);

  E->len--;
  E->cursor_index--;

  E->dirty = 1;
}

void copy_line(EditorState *E)
{
  E->clipboard_len = 0;

  if (E->len == 0)
    return;

  /* find line start */
  int start = E->cursor_index;

  while (start > 0 && E->buffer[start - 1] != '\n')
    start--;

  /* find line end */
  int end = E->cursor_index;

  while (end < E->len && E->buffer[end] != '\n')
    end++;

  /* copy */
  for (int i = start; i < end; i++)
  {
    if (E->clipboard_len < (int)sizeof(E->clipboard))
      E->clipboard[E->clipboard_len++] = E->buffer[i];
  }
}

void paste_clipboard(EditorState *E)
{
  for (int i = 0; i < E->clipboard_len; i++)
  {
    insert_char(E, E->clipboard[i]);
  }
}

void editor_open(EditorState *E)
{

  int fd = open(E->filename, O_RDONLY);
  if (fd == -1)
    return;

  char temp[4096];
  int n;

  while ((n = read(fd, temp, sizeof(temp))) > 0)
  {

    // grow if needed
    if (E->len + n >= E->capacity)
    {
      while (E->len + n >= E->capacity)
        E->capacity *= 2;

      E->buffer = realloc(E->buffer, E->capacity);

      if (!E->buffer)
      {
        perror("realloc");
        exit(1);
      }
    }

    memcpy(E->buffer + E->len, temp, n);
    E->len += n;
  }

  close(fd);
}

int save_file(EditorState *E)
{

  int fd = open(E->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd == -1)
  {
    editor_set_status(E, "Save failed");
    return -1;
  }

  int total_written = 0;

  while (total_written < E->len)
  {
    int n = write(fd, E->buffer + total_written, E->len - total_written);

    if (n == -1)
    {
      close(fd);
      editor_set_status(E, "Save failed");
      return -1;
    }

    total_written += n;
  }

  if (close(fd) == -1)
    return -1;

  E->dirty = 0;
  editor_set_status(E, "saved");

  return 0;
}
