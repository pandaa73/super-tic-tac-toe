#include <gui.h>

void gui_button_drawer(gui_element_t *button) {
    if(!button || !button->style ||
       *(gui_t *)button->style != GUI_BUTTON) return;

    gui_button_style_t *style = (gui_button_style_t *)button->style;

    Color colour, colour_text;
    switch(button->state) {
        case GUISTATE_HOVERED: {
            colour = style->hovered_c;
            if(style->text) colour_text = style->text_hovered_c;
            break;
        }

        case GUISTATE_PRESSED: {
            colour = style->pressed_c;
            if(style->text) colour_text = style->text_pressed_c;
            break;
        }

        case GUISTATE_DISABLED: {
            colour = style->disabled_c;
            if(style->text) colour_text = style->text->disabled_c;
            break;
        }

        default: {
            colour = style->default_c;
            if(style->text) colour_text = style->text->default_c;
            break;
        }
    }

    if(style->texture == TEX_NONE || style->texture >= TEX_SIZE) {
        DrawRectangle(
            button->x,
            button->y,
            button->width,
            button->height,
            colour        
        );

    } else {
        draw_texture(
            style->texture,
            button->x,
            button->y,
            colour
        );
    }

    if(!style->text) return;

    Vector2 text_size = measure_text(
        style->text->text,
        style->text->size,
        style->text->x_spacing,
        style->text->y_spacing
    );

    int text_x = button->x + (button->width - text_size.x) / 2;
    int text_y = button->y + (button->height - text_size.y) / 2;

    draw_text(
        style->text->text,
        text_x,
        text_y,
        style->text->size,
        style->text->x_spacing,
        style->text->y_spacing,
        colour_text
    );
}

void gui_button_handler(gui_element_t *button) {
    if(!button || button->state == GUISTATE_DISABLED) return;

    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    if(mouseX < button->x || mouseX > button->x + button->width ||
       mouseY < button->y || mouseY > button->y + button->height) {
        button->state = GUISTATE_DEFAULT;
        return;
    }

    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        button->state = GUISTATE_DEFAULT;
        button->callback(button);
        return;
    }

    if(!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        button->state = GUISTATE_HOVERED;
        return;
    }

    button->state = GUISTATE_PRESSED;
}