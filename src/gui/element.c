#include <gui.h>

void gui_enable_element(gui_element_t *element) {
    if(!element) return;

    element->state = GUISTATE_DEFAULT;
}

void gui_disable_element(gui_element_t *element) {
    if(!element) return;

    element->state = GUISTATE_DISABLED;
}