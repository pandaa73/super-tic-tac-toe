#include <textures.h>
#include <settings.h>
#include <defs.h>
#include <string.h>

Texture2D tex_buffer[TEX_SIZE];

void draw_texture(texture_t texture, int x, int y, Color colour) {
    if(!IsTextureReady(tex_buffer[texture])) return;

    DrawTexture(tex_buffer[texture], x, y, colour);
}

void draw_texture_rec(texture_t texture, int x, int y, Color colour,
   Rectangle source) {
    if(!IsTextureReady(tex_buffer[texture])) return;

    DrawTextureRec(tex_buffer[texture], source, (Vector2){x, y}, colour);
}

void load_texture(texture_t texture, bool autoscale) {
    if(texture >= TEX_SIZE || texture <= TEX_NONE) return;
    if(IsTextureReady(tex_buffer[texture])) return;

    Image tmp;
    int scale = autoscale ? get_window_width() / 240 : 1;

    switch(texture) {
        case TEX_BACKGROUND:
            tmp = LoadImage("assets/background.png"); break;

        case TEX_BUTTON12:
            tmp = LoadImage("assets/button12.png"); break;
        
        case TEX_TITLE:
            tmp = LoadImage("assets/title.png"); break;
        
        case TEX_SETTINGS:
            tmp = LoadImage("assets/settings.png"); break;
    }

    if(!IsImageReady(tmp)) {
        TraceLog(LOG_FATAL, "Failed to load image");
    }

    ImageResizeNN(&tmp, tmp.width * scale, tmp.height * scale);
    tex_buffer[texture] = LoadTextureFromImage(tmp);

    if(!IsTextureReady(tex_buffer[texture])) {
        TraceLog(LOG_FATAL, "Failed to log texture");
    }

    UnloadImage(tmp);
}

void unload_all_textures(void) {
    for(texture_t it = TEX_NONE; it < TEX_SIZE; ++it) {
        if(IsTextureReady(tex_buffer[it])) UnloadTexture(tex_buffer[it]);
    }

    memset(tex_buffer, 0x00, sizeof(tex_buffer));
}