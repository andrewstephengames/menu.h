#include "menu.h"

Vector2 rec_to_v (Rectangle rec) {
     return (Vector2) { rec.x, rec.y };
}

void mouse_on_element (Element *e) {
     Vector2 mouse = GetMousePosition();
     if (CheckCollisionPointRec (mouse, e->box)) {
          e->bg.a = 0x80;
     } else {
          e->bg.a = 0xFF;
     }
}

Element *draw_button (Element *e, bool texture) {
     mouse_on_element (e);
     if (texture) {
          DrawTextureRec (e->texture, e->box, rec_to_v(e->box), e->bg);
     } else {
          DrawRectangleRec (e->box, e->bg);
     }
     return e;
}

void center_element (Element *e, Vector2 canvas) {
     float x = canvas.x/2-MeasureText(e->label, e->label_size)/2;
     float y = canvas.y/2-e->label_size/2;
     e->box.x = x;
     e->box.y = y;
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
     mouse_on_element (e);
}

//Element *draw_input (Element *e, 
