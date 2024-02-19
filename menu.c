#include "menu.h"

Vector2 rec_to_v (Rectangle rec) {
     return (Vector2) { rec.x, rec.y };
}

void center_element (Element *e, Vector2 canvas) {
     float x = canvas.x/2-MeasureText(e->label, e->label_size)/2;
     float y = canvas.y/2-e->label_size/2;
     e->box.x = x;
     e->box.y = y;
}

void mouse_on_element (Element *e, void (*l_func) (void), void (*r_func) (void)) {
     Vector2 mouse = GetMousePosition();
     if (CheckCollisionPointRec (mouse, e->box)) {
          e->bg.a = 127;
          if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT) && l_func != NULL) {
               (*l_func)();
          }
          if (IsMouseButtonPressed (MOUSE_BUTTON_RIGHT) && r_func != NULL) {
               (*r_func)();
          }
     } else {
          e->bg.a = 255;
     }
}

void draw_button (Element *e, bool texture, bool center, Vector2 canvas, 
                  void (*l_func) (void), void (*r_func) (void)) {
     if (center) {
          center_element (e, canvas);
     }
     e->box.width = MeasureText(e->label, e->label_size);
     e->box.height = e->label_size;
     if (texture) {
          DrawTextureRec (e->texture, e->box, rec_to_v(e->box), e->bg);
     } else {
          DrawRectangleRec (e->box, e->bg);
     }
     DrawText (e->label, e->box.x, e->box.y, e->label_size, e->fg);
     mouse_on_element (e, l_func, r_func);
}

void draw_label (Element *e, Vector2 canvas, bool texture) {
     center_element (e, canvas);
     e->box.width = MeasureText(e->label, e->label_size);
     e->box.height = e->label_size;
     if (texture) {
          DrawTextureRec (e->texture, e->box, rec_to_v (e->box), e->bg);
     } else {
          DrawRectangleRec (e->box, e->bg);
     }
     DrawText (e->label, e->box.x, e->box.y, e->label_size, e->fg);
}

// FIXME: Characters not getting drawn
void draw_input (Element *e, Vector2 canvas, bool texture) {
     bool is_selected = false;
     center_element (e, canvas);
     e->box.width = MeasureText(e->label, e->label_size);
     e->box.height = e->label_size;
     if (texture) {
          DrawTextureRec (e->texture, e->box, rec_to_v (e->box), e->bg);
     } else {
          DrawRectangleRec (e->box, e->bg);
     }
     if (strlen(e->label) == 0) {
          strcpy (e->label, "Type..");
     }
     DrawText (e->label, e->box.x, e->box.y, e->label_size, e->fg);
     if (CheckCollisionPointRec (GetMousePosition(), e->box)) {
          SetMouseCursor (MOUSE_CURSOR_IBEAM);
          e->fg.a = 255;
          if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
               is_selected = true;
          }
     } else {
          SetMouseCursor (MOUSE_CURSOR_DEFAULT);
          e->fg.a = 50;
          if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
               is_selected = false;
          }
     }
     if (is_selected) {
          int key = GetCharPressed();
          if (key >= 32 && key <= 125) {
               size_t len = strlen(e->label);
               if (len < sizeof (e->label)-1) {
                    e->label[len] = (char) key;
                    e->label[++len] = '\0';
               }
          } else if (key == KEY_BACKSPACE) {
               size_t len = strlen(e->label);
               if (len > 0) {
                    e->label[len-1] = '\0';
               }
          }
     }
}
