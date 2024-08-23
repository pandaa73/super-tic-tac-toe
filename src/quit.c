#include <quit.h>
#include <font.h>
#include <textures.h>

#include <raylib.h>
#include <stdlib.h>

void quit(void) {
    unload_font();
    unload_all_textures();

    CloseWindow();

    exit(EXIT_SUCCESS);
}