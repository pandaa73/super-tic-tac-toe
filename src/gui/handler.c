#include <gui.h>
#include <defs.h>

#include <string.h>

void gui_handler_drawer(gui_handler_t *handler) {
    for(size_t i = 0; i < MAX_ELEMENT_COUNT; ++i) {
        if(!handler->elements[i]) break;

        switch(*(gui_t *)handler->elements[i]) {
            case GUI_BUTTON: {
                gui_button_drawer(handler->elements[i]);
                break;
            }

            case GUI_TEXTDISPLAY: {
                gui_textdisplay_drawer(handler->elements[i]);
                break;
            }
        }
    }
}

void gui_handler_handler(gui_handler_t *handler) {
    for(size_t i = 0; i < MAX_ELEMENT_COUNT; ++i) {
        if(!handler->elements[i]) break;

        switch(*(gui_t *)handler->elements[i]) {
            case GUI_BUTTON: {
                gui_button_handler(handler->elements[i]);
                break;
            }
        }
    }
}

void gui_init_handler(gui_handler_t *handler) {
    memset(handler->elements, 0x00, sizeof(handler->elements));
}

int gui_add_element(gui_handler_t *handler, gui_element_t *element) {
    for(size_t i = 0; i < MAX_ELEMENT_COUNT; ++i) {
        if(handler->elements[i]) continue;
        handler->elements[i] = element;

        break;
    }
}

int gui_remove_element(gui_handler_t *handler, gui_element_t *element) {
    for(size_t i = 0; i < MAX_ELEMENT_COUNT; ++i) {
        if(handler->elements[i] != element) continue;
        handler->elements[i] = 0x00;
        
        for(size_t j = i; j < MAX_ELEMENT_COUNT - 1; ++j) {
            if(!handler->elements[j]) break;

            handler->elements[j] = handler->elements[j + 1];
        }

        break;
    }
}