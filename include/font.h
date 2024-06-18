#ifndef __STTT_FONT_H
#define __STTT_FONT_H

#include <raylib.h>

typedef enum {
    FONTSZ_DEFAULT,
    FONTSZ_SIZE
} fontsize_t;

void init_font(void);

void draw_text(const char *text, int x, int y, fontsize_t size, int x_spacing,
   int y_spacing, Color colour);

Vector2 measure_text(const char *text, fontsize_t size, int x_spacing,
   int y_spacing);

#endif /* _STTT_FONT_H */