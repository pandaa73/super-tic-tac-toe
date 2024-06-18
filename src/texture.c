#include <texture.h>

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
    if(texture >= TEX_SIZE) return;

    Image tmp;
    int scale = autoscale ? GetScreenWidth() / 240 : 1;

    switch(texture) {
        case TEX_BACKGROUND:
            tmp = LoadImage("assets/background.png"); break;

        case TEX_BUTTON12:
            tmp = LoadImage("assets/button12.png"); break;
        
        case TEX_TITLE:
            tmp = LoadImage("assets/title.png"); break;
    }

    if(!IsImageReady(tmp)) {
        TraceLog(LOG_FATAL, "Failed to load image");
    }

    ImageResizeNN(&tmp, tmp.width * scale, tmp.height * scale);
    tex_buffer[texture] = LoadTextureFromImage(tmp);

    if(!IsTextureReady(tex_buffer[texture])) {
        TraceLog(LOG_FATAL, "Failed to log texture");
    }
}