#ifndef RENDER_H
#define RENDER_H

#include "editor.h"

void refresh_screen(EditorState *E);
void editor_index_to_xy(EditorState *E, int *x, int *y);

#endif