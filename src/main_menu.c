#include <main_menu.h>
#include <variables.h>
#include <game.h>
#include <font.h>
#include <gui.h>
#include <settings.h>
#include <quit.h>

static bool init = 0;
static gui_handler_t handler;

gui_element_t       offline_button;
gui_button_style_t  offline_style;

gui_element_t       online_button;
gui_button_style_t  online_style;

gui_element_t       settings_button;
gui_button_style_t  settings_style;

gui_element_t       quit_button;
gui_button_style_t  quit_style;

void offline_callback(void *self) {
    init_game();

    event_handler = game_event_handler;
    screen_drawer = game_screen_drawer;
}

void online_callback(void *self) { return; }

void settings_callback(void *self) {
    init_settings();

    event_handler = settings_event_handler;
    screen_drawer = settings_screen_drawer;
}

void quit_callback(void *self) {
    quit();
}

static gui_button_style_t base_style_button = {
    GUI_BUTTON,                                         /* type */ 
    WHITE, WHITE, WHITE, BLANK,                         /* colours */
    TEX_BUTTON12,                                       /* texture */
    YELLOW, LIGHTGRAY                                   /* text colours */
};                                                      /* text */

gui_textdisplay_style_t offline_text = {
    GUI_TEXTDISPLAY,                                    /* type */
    "PLAY OFFLINE",                                     /* text */
    -1, -1, FONTSZ_DEFAULT,                             /* spacing & size */
    WHITE, BLANK                                        /* text colours */
};                                                      

gui_textdisplay_style_t online_text = {
    GUI_TEXTDISPLAY,                                    /* type */ 
    "PLAY ONLINE",                                      /* text */
    -1, -1, FONTSZ_DEFAULT,                             /* spacing & size */
    WHITE, BLANK                                        /* text colours */
};                                                      

gui_textdisplay_style_t settings_text = {
    GUI_TEXTDISPLAY,                                    /* type */
    "SETTINGS",                                         /* text */
    -1, -1, FONTSZ_DEFAULT,                             /* spacing & size */
    WHITE, BLANK                                        /* text colours */
};                                                      

gui_textdisplay_style_t quit_text = {
    GUI_TEXTDISPLAY,                                    /* type */
    "QUIT",                                             /* text */
    -1, -1, FONTSZ_DEFAULT,                             /* spacing & size */
    WHITE, BLANK                                        /* text colours */
};

void init_main_menu(void) {
    load_texture(TEX_BACKGROUND, 1);
    load_texture(TEX_BUTTON12, 1);
    load_texture(TEX_TITLE, 1);

    gui_init_handler(&handler);

    int width = get_window_width();
    int height = get_window_height();

    int scale = width / 240;

    /* -- Offline Play Button & Text Display -- */

    offline_style           = base_style_button;
    offline_style.text      = &offline_text;

    offline_button.type     = GUI_BUTTON;
    offline_button.state    = GUISTATE_DEFAULT;
    offline_button.x        = 21 * scale;
    offline_button.y        = 64 * scale;
    offline_button.width    = 81 * scale;
    offline_button.height   = 16 * scale;
    offline_button.callback = offline_callback;
    offline_button.style    = &offline_style;

    gui_add_element(&handler, &offline_button);

    /* -- Online Play Button & Text Display -- */

    online_style           = base_style_button;
    online_style.text      = &online_text;

    online_button.type     = GUI_BUTTON;
    online_button.state    = GUISTATE_DEFAULT;
    online_button.x        = 138 * scale;
    online_button.y        =  64 * scale;
    online_button.width    = 81 * scale;
    online_button.height   = 16 * scale;
    online_button.callback = online_callback;
    online_button.style    = &online_style;

    gui_add_element(&handler, &online_button);

    /* -- Settings Button & Text Display -- */

    settings_style           = base_style_button;
    settings_style.text      = &settings_text;

    settings_button.type     = GUI_BUTTON;
    settings_button.state    = GUISTATE_DEFAULT;
    settings_button.x        = 21 * scale;
    settings_button.y        = 88 * scale;
    settings_button.width    = 81 * scale;
    settings_button.height   = 16 * scale;
    settings_button.callback = settings_callback;
    settings_button.style    = &settings_style;

    gui_add_element(&handler, &settings_button);

    /* -- Quit Button & Text Display -- */

    quit_style           = base_style_button;
    quit_style.text      = &quit_text;

    quit_button.type     = GUI_BUTTON;
    quit_button.state    = GUISTATE_DEFAULT;
    quit_button.x        = 138 * scale;
    quit_button.y        =  88 * scale;
    quit_button.width    = 81 * scale;
    quit_button.height   = 16 * scale;
    quit_button.callback = quit_callback;
    quit_button.style    = &quit_style;

    gui_add_element(&handler, &quit_button);
}

void main_menu_event_handler(void) {
    gui_handler_handler(&handler);
}

void main_menu_screen_drawer(void) {
    int width = get_window_width();
    int height = get_window_height();

    int scale = width / 240;

    draw_texture(TEX_BACKGROUND, 0, 0, WHITE);
    draw_texture(TEX_TITLE, 21 * scale, 24 * scale, WHITE);

    gui_handler_drawer(&handler);
}