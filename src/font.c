#include <font.h>
#include <settings.h>

#include <string.h>

Texture2D font_tx[FONTSZ_SIZE];
int font_sz[FONTSZ_SIZE];

void init_font(void) {
    Image font_default_i = LoadImage("assets/font.png");
    if(!IsImageReady(font_default_i)) {
        TraceLog(LOG_FATAL, "Failed to load font into image");
    }

    font_sz[FONTSZ_DEFAULT] = get_window_width() / 240;

    ImageResizeNN(
        &font_default_i,
        80 * font_sz[FONTSZ_DEFAULT],
        64 * font_sz[FONTSZ_DEFAULT]
    );

    font_tx[FONTSZ_DEFAULT] = LoadTextureFromImage(font_default_i);
    if(!IsTextureReady(font_tx[FONTSZ_DEFAULT])) {
        TraceLog(LOG_FATAL, "Failed to load font into texture");
    }

    UnloadImage(font_default_i);
}

void unload_font(void) {
    for(fontsize_t it = FONTSZ_DEFAULT; it < FONTSZ_SIZE; it++) {
        if(IsTextureReady(font_tx[it])) UnloadTexture(font_tx[it]);
    }

    memset(font_tx, 0x00, sizeof(font_tx));
}

void draw_text(const char *text, int x, int y, fontsize_t size, int x_spacing,
   int y_spacing, Color colour) {
    if(!text || size >= FONTSZ_SIZE) return;
    if(x_spacing == -1) {
        x_spacing = font_sz[size];
    }

    if(y_spacing == -1) {
        y_spacing = font_sz[size];
    }

    int next_x = x;
    int next_y = y;

    while(*text != 0) {
        if(*text == '\n') {
            next_x = x;
            next_y += y_spacing + 8 * font_sz[size];

            text++;
            continue;
        }

        int char_x = 5 * font_sz[size] * (*text % 16);
        int char_y = 8 * font_sz[size] * (*text / 16);

        DrawTextureRec(
            font_tx[size],
            (Rectangle){
                char_x,
                char_y,
                5 * font_sz[size],
                8 * font_sz[size]
            },
            (Vector2){
                next_x,
                next_y
            },
            colour
        );

        next_x += x_spacing + 5 * font_sz[size];
        text++;
    }
}

Vector2 measure_text(const char *text, fontsize_t size, int x_spacing,
   int y_spacing) {
    if(!text || size >= FONTSZ_SIZE) return (Vector2){ 0, 0 };
    if(x_spacing == -1) {
        x_spacing = font_sz[size];
    }

    if(y_spacing == -1) {
        y_spacing = font_sz[size];
    }

    int max_width = 0;

    int width = 0;
    int height = 0;

    while(*text != 0) {
        if(*text == '\n') {
            width -= x_spacing;
            max_width = width > max_width ? width : max_width;
            width = 0;
            height += y_spacing + 8 * font_sz[size];

            text++;
            continue;
        }

        width += x_spacing + 5 * font_sz[size];
        text++;
    }

    width -= x_spacing;
    height += 8 * font_sz[size];

    max_width = width > max_width ? width : max_width;

    return (Vector2){ max_width, height };
}