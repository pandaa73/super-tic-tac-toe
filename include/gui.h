#ifndef __STTT_GUI_H
#define __STTT_GUI_H

#include <font.h>
#include <texture.h>

#include <raylib.h>

#define MAX_ELEMENT_COUNT   512

typedef void (*gui_callback_t)(void *self);

typedef enum {
    GUI_NONE,
    GUI_BUTTON,
    GUI_TEXTDISPLAY
} gui_t;

typedef enum {
    GUISTATE_DEFAULT,
    GUISTATE_HOVERED,
    GUISTATE_PRESSED,
    GUISTATE_DISABLED
} gui_state_t;

typedef struct {
    gui_t type;
    gui_state_t state;
    
    int x;
    int y;
    int width;
    int height;

    gui_callback_t callback;
    void *style;
} gui_element_t;

typedef struct {
    gui_t type;

    char *text;

    int x_spacing;
    int y_spacing;
    fontsize_t size;

    Color default_c;
    Color disabled_c;
} gui_textdisplay_style_t;

typedef struct {
    gui_t type;

    Color default_c;
    Color hovered_c;
    Color pressed_c;
    Color disabled_c;

    texture_t texture;

    Color text_hovered_c;
    Color text_pressed_c;
    gui_textdisplay_style_t *text;
} gui_button_style_t;

typedef struct {
    gui_element_t *elements[MAX_ELEMENT_COUNT];
} gui_handler_t;

void gui_button_drawer(gui_element_t *button);
void gui_button_handler(gui_element_t *button);

void gui_textdisplay_drawer(gui_element_t *textdisplay);

void gui_handler_drawer(gui_handler_t *handler);
void gui_handler_handler(gui_handler_t *handler);

void gui_enable_element(gui_element_t *element);
void gui_disable_element(gui_element_t *element);

void gui_init_handler(gui_handler_t *handler);
int gui_add_element(gui_handler_t *handler, gui_element_t *element);
int gui_remove_element(gui_handler_t *handler, gui_element_t *element);

#endif /* __STTT_GUI_H */