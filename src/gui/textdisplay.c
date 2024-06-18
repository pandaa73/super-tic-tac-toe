#include <gui.h>
#include <font.h>

void gui_textdisplay_drawer(gui_element_t *textdisplay) {
    if(!textdisplay || !textdisplay->style ||
       *(gui_t *)textdisplay->style != GUI_TEXTDISPLAY) return;

    gui_textdisplay_style_t *style = 
        (gui_textdisplay_style_t *)textdisplay->style;

    Color colour;
    switch(textdisplay->state) {
        case GUISTATE_DISABLED: {
            colour = style->disabled_c;
            break;
        }

        default: {
            colour = style->default_c;
            break;
        }
    }

    draw_text(
        style->text,
        textdisplay->x,
        textdisplay->y,
        style->size,
        style->x_spacing,
        style->y_spacing,
        colour
    );
}