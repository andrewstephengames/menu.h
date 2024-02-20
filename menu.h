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
     char label[MAX_INPUT_SIZE];
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
void draw_background (Vector2 canvas, float alpha, Texture2D texture);

Vector2 rec_to_v (Rectangle rec) {
     return (Vector2) { rec.x, rec.y };
}

void center_element (Element *e, Vector2 canvas) {
     float x = canvas.x/2-MeasureText(e->label, e->font_size)/2;
     float y = canvas.y/2-e->font_size/2;
     e->box.x = x;
     e->box.y = y;
}

void mouse_on_element (Element *e, void (*l_func) (void), void (*r_func) (void)) {
     Vector2 mouse = GetMousePosition();
     if (CheckCollisionPointRec (mouse, e->box)) {
          e->bg.a = 255;
          if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT) && l_func != NULL) {
               (*l_func)();
          }
          if (IsMouseButtonPressed (MOUSE_BUTTON_RIGHT) && r_func != NULL) {
               (*r_func)();
          }
     } else {
          e->bg.a = 127;
     }
}

void draw_button (Element *e, bool texture, bool center, Vector2 canvas, 
                  void (*l_func) (void), void (*r_func) (void)) {
     if (center) {
          center_element (e, canvas);
     }
     e->box.width = MeasureText(e->label, e->font_size);
     e->box.height = e->font_size;
     if (texture) {
          DrawTextureRec (e->texture, e->box, rec_to_v(e->box), e->bg);
     } else {
          DrawRectangleRec (e->box, e->bg);
     }
     DrawText (e->label, e->box.x, e->box.y, e->font_size, e->fg);
     mouse_on_element (e, l_func, r_func);
}

void draw_label (Element *e, bool texture, bool center, Vector2 canvas) {
     if (center) {
          center_element (e, canvas);
     }
     e->box.width = MeasureText(e->label, e->font_size);
     e->box.height = e->font_size;
     if (texture) {
          DrawTextureRec (e->texture, e->box, rec_to_v (e->box), e->bg);
     } else {
          DrawRectangleRec (e->box, e->bg);
     }
     DrawText (e->label, e->box.x, e->box.y, e->font_size, e->fg);
}

void draw_input(Element *e, bool texture, bool center, Vector2 canvas) {
     Vector2 mouse = GetMousePosition();
     bool is_mouse_on_box = CheckCollisionPointRec (mouse, e->box);
     Vector2 w = {
          .x = canvas.x/2 - e->box.width/2,
          .y = canvas.y/2 - e->box.height/2,
     };
     if (center) {
          e->box.x = w.x;
          e->box.y = w.y;
     }
     if (texture) {
          DrawTextureRec (e->texture, e->box, rec_to_v(e->box), e->fg);
     } else {
          DrawRectangleRec(e->box, e->bg);
     }
     if (e->label_len == 0) {
          DrawText("Type..", e->box.x + 10, e->box.y + e->box.height / 2 - 10, e->font_size, e->fg);
     } else {
          DrawText(e->label, e->box.x + 10, e->box.y + e->box.height / 2 - 10, e->font_size, e->fg);
     }
     int key = GetCharPressed();
     if (is_mouse_on_box) {
          SetMouseCursor(MOUSE_CURSOR_IBEAM);
          DrawText("|", e->box.x + 10 + MeasureText(e->label, e->font_size), e->box.y + e->box.height / 2 - 10, e->font_size, e->fg);
          if (key != 0) {
               if (e->font_size < MAX_INPUT_SIZE - 1) {
                    e->label[e->label_len++] = (char)key;
                    e->label[e->label_len] = '\0';
               }
          } else if (IsKeyPressed(KEY_BACKSPACE) && e->label_len > 0) {
               e->label[--e->label_len] = '\0';
          }
     } else {
          SetMouseCursor(MOUSE_CURSOR_DEFAULT);
     }
}

void draw_background (Vector2 canvas, float alpha, Texture2D texture) {
     Color c = WHITE;
     c.a = alpha;
     Rectangle rect = {
          .width = canvas.x,
          .height = canvas.y,
     };
     if (texture.id > 0) {
          SetShapesTexture (texture, rect);
     }
     DrawRectangle (0, 0, canvas.x, canvas.y, c);
}

#endif // MENU_H_
