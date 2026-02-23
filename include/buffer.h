#ifndef BUFFER_H
#define BUFFER_H

#include "editor.h"

void ensure_capacity(EditorState *E, int needed);
void insert_char(EditorState *E, char c);
void insert_newline(EditorState *E);
void delete_char(EditorState *E);
void copy_line(EditorState *E);
void paste_clipboard(EditorState *E);
void editor_open(EditorState *E);
int save_file(EditorState *E);

#endif