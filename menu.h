#ifndef MENU_H_
#define MENU_H_

#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
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
void center_element (Element *e, Vector2 canvas);
void mouse_on_element (Element *e, void (*l_func) (void), void (*r_func) (void));
void draw_button (Element *e, bool texture, bool center, Vector2 canvas, 
                  void (*l_func) (void), void (*r_func) (void));
void draw_label (Element *e, Vector2 canvas, bool texture);
void draw_input (Element *e, Vector2 canvas, bool texture);

#endif // MENU_H_
