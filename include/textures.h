#ifndef __STTT_TEXTURE_H
#define __STTT_TEXTURE_H

#include <raylib.h>

typedef enum {
    TEX_NONE,
    TEX_BACKGROUND,
    TEX_BUTTON12,
    TEX_TITLE,
    TEX_SETTINGS,
    TEX_SIZE
} texture_t;

void draw_texture(texture_t texture, int x, int y, Color colour);
void draw_texture_rec(texture_t texture, int x, int y, Color colour,
   Rectangle source);

void load_texture(texture_t texture, bool autoscale);

void unload_all_textures(void);

#endif /* __STTT_TEXTURE_H */