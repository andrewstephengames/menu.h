#ifndef MENU_H_
#define MENU_H_

#include <raylib.h>
#include <stddef.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif // __cplusplus

typedef struct {
     Rectangle box;
     char *label;
     size_t label_size;
     Color bg;
     Color fg;
     Texture2D texture;
} Element;

Vector2 rec_to_v (Rectangle rec);
void mouse_on_element (Element *e);
Element *draw_button (Element *e, bool texture);
void center_element (Element *e, Vector2 canvas);
void draw_label (Element *e, Vector2 canvas, bool texture);

#endif // MENU_H_
