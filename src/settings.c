#include <settings.h>
#include <main_menu.h>
#include <variables.h>
#include <textures.h>
#include <font.h>
#include <gui.h>

#include <raylib.h>
#include <string.h>

#define RESOLUTION_COUNT 8

settings_t settings;

static int resolution_widths[RESOLUTION_COUNT] = {
    240,  480,
    720,  960,
    1200, 1440,
    1680, 1920
};

static int resolution_heights[RESOLUTION_COUNT] = {
    135, 270,
    405, 540,
    675, 810,
    945, 1080
};

static char *resolution_strings[RESOLUTION_COUNT] = {
    "240X135",  "480X270",
    "720X405",  "960X540",
    "1200X675", "1440X810",
    "1680X945", "1920X1080"
};

static bool init = 0;
static gui_handler_t handler;

gui_element_t       resolution_button;
gui_button_style_t  resolution_style;

gui_element_t       empty0_button;
gui_button_style_t  empty0_style;

gui_element_t       empty1_button;
gui_button_style_t  empty1_style;

gui_element_t       save_button;
gui_button_style_t  save_style;

void resolution_callback(void *self) {
    settings.resolution = (settings.resolution + 1) % RESOLUTION_COUNT;

    int width  = resolution_widths[settings.resolution];
    int height = resolution_heights[settings.resolution];

    int monitor_width  = GetMonitorWidth(GetCurrentMonitor());
    int monitor_height = GetMonitorHeight(GetCurrentMonitor());

    SetWindowSize(width, height);
    SetWindowPosition(
        monitor_width  / 2 - width  / 2,
        monitor_height / 2 - height / 2
    );

    unload_font();
    unload_all_textures();

    init_font();
    init_settings();
}

void save_callback(void *self) {
    save_settings();
    init_main_menu();

    event_handler = main_menu_event_handler;
    screen_drawer = main_menu_screen_drawer;
}

static gui_button_style_t base_style_button = {
    GUI_BUTTON,                                         /* type */
    WHITE, WHITE, WHITE, BLANK,                         /* colours */
    TEX_BUTTON12,                                       /* texture */
    YELLOW, LIGHTGRAY,                                  /* text colours */
    NULL                                                /* text */
};

gui_textdisplay_style_t resolution_text = {
    GUI_TEXTDISPLAY,                                    /* type */
    "EMPTY",                                            /* text */
    -1, -1, FONTSZ_DEFAULT,                             /* spacing & size */
    WHITE, BLANK                                        /* text colours */
};

gui_textdisplay_style_t empty0_text = {
    GUI_TEXTDISPLAY,                                    /* type */
    "EMPTY",                                            /* text */
    -1, -1, FONTSZ_DEFAULT,                             /* spacing & size */
    WHITE, BLANK                                        /* text colours */
};

gui_textdisplay_style_t empty1_text = {
    GUI_TEXTDISPLAY,                                    /* type */
    "EMPTY",                                            /* text */
    -1, -1, FONTSZ_DEFAULT,                             /* spacing & size */
    WHITE, BLANK                                        /* text colours */
};

gui_textdisplay_style_t save_text = {
    GUI_TEXTDISPLAY,                                    /* type */
    "SAVE",                                             /* text */
    -1, -1, FONTSZ_DEFAULT,                             /* spacing & size */
    WHITE, BLANK                                        /* text colours */
};

void init_settings(void) {
    load_texture(TEX_BACKGROUND, 1);
    load_texture(TEX_BUTTON12, 1);
    load_texture(TEX_SETTINGS, 1);

    gui_init_handler(&handler);

    int width  = get_window_width();
    int height = get_window_height();

    int scale = width / 240;

    /* -- Resolution Button & Text Display -- */

    resolution_text.text       = resolution_strings[settings.resolution];

    resolution_style           = base_style_button;
    resolution_style.text      = &resolution_text;

    resolution_button.type     = GUI_BUTTON;
    resolution_button.state    = GUISTATE_DEFAULT;
    resolution_button.x        = 21 * scale;
    resolution_button.y        = 64 * scale;
    resolution_button.width    = 81 * scale;
    resolution_button.height   = 16 * scale;
    resolution_button.callback = resolution_callback;
    resolution_button.style    = &resolution_style;

    gui_add_element(&handler, &resolution_button);

    /* -- Empty Button & Text Display -- */

    empty0_style           = base_style_button;
    empty0_style.text      = &empty0_text;

    empty0_button.type     = GUI_BUTTON;
    empty0_button.state    = GUISTATE_DEFAULT;
    empty0_button.x        = 138 * scale;
    empty0_button.y        =  64 * scale;
    empty0_button.width    = 81 * scale;
    empty0_button.height   = 16 * scale;
    empty0_button.callback = NULL;
    empty0_button.style    = &empty0_style;

    gui_add_element(&handler, &empty0_button);

    /* -- Empty Button & Text Display -- */

    empty1_style           = base_style_button;
    empty1_style.text      = &empty1_text;

    empty1_button.type     = GUI_BUTTON;
    empty1_button.state    = GUISTATE_DEFAULT;
    empty1_button.x        = 21 * scale;
    empty1_button.y        = 88 * scale;
    empty1_button.width    = 81 * scale;
    empty1_button.height   = 16 * scale;
    empty1_button.callback = NULL;
    empty1_button.style    = &empty1_style;

    gui_add_element(&handler, &empty1_button);

    /* -- Save Button & Text Display -- */

    save_style           = base_style_button;
    save_style.text      = &save_text;

    save_button.type     = GUI_BUTTON;
    save_button.state    = GUISTATE_DEFAULT;
    save_button.x        = 138 * scale;
    save_button.y        =  88 * scale;
    save_button.width    = 81 * scale;
    save_button.height   = 16 * scale;
    save_button.callback = save_callback;
    save_button.style    = &save_style;

    gui_add_element(&handler, &save_button);
}

void settings_event_handler(void) {
    gui_handler_handler(&handler);
}

void settings_screen_drawer(void) {
    int width = get_window_width();
    int height = get_window_height();

    int scale = width / 240;

    draw_texture(TEX_BACKGROUND, 0, 0, WHITE);
    draw_texture(TEX_SETTINGS, 21 * scale, 24 * scale, WHITE);

    gui_handler_drawer(&handler);
}

void save_settings(void) {
    if(!SaveFileData("settings", &settings, sizeof(settings)))
        TraceLog(LOG_ERROR, "Failed to saved settings.");
}

void load_settings_current(byte_t *data) {
    memcpy(&settings, data, (int)*(data + sizeof(int)));
}

void load_settings(void) {
    int size = 2 * sizeof(int);
    byte_t *data = LoadFileData("settings", &size);

    int version = (int)*data;
        size    = (int)*(data + sizeof(int));
    UnloadFileData(data);

    data = LoadFileData("settings", &size);

    switch(version) {
        default: load_settings_current(data); break;
    }

    UnloadFileData(data);
}

void load_settings_default(void) {
    settings.version = 0;
    settings.size = sizeof(settings_t);
    
    settings.resolution = 4;
}

int get_window_width(void) {
    return resolution_widths[settings.resolution];
}

int get_window_height(void) {
    return resolution_heights[settings.resolution];
}