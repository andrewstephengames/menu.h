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
#define MAX_INPUT_SIZE 1024

typedef struct {
     Rectangle box;
     char label[1024];
     int label_len;
     size_t font_size;
     Color bg;
     Color fg;
     Texture2D texture;
} Element;

Vector2 rec_to_v (Rectangle rec);
void center_element (Element *e, Vector2 canvas);
void mouse_on_element (Element *e, void (*l_func) (void), void (*r_func) (void));
void draw_button (Element *e, bool texture, bool center, Vector2 canvas, 
                  void (*l_func) (void), void (*r_func) (void));
void draw_label (Element *e, bool texture, bool center, Vector2 canvas);
void draw_input (Element *e, bool texture, bool center, Vector2 canvas);

#endif // MENU_H_
