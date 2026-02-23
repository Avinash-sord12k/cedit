#ifndef STATUS_H
#define STATUS_H

#include "editor.h"

void editor_set_status(EditorState *E, const char *fmt, ...);
void draw_status_bar(EditorState *E);

#endif