#include <variables.h>
#include <main_menu.h>
#include <font.h>
#include <settings.h>
#include <quit.h>

#include <raylib.h>

int main(void) {
    load_settings();
    // load_settings_default();

    InitWindow(get_window_width(), get_window_height(), "Super Tic-Tac-Toe!");

    if(!IsWindowReady()) TraceLog(LOG_FATAL, "Failed to created window.");

    init_main_menu();
    init_font();

    while(!WindowShouldClose()) {
        ClearBackground(BLACK);

        event_handler();

        BeginDrawing();
            screen_drawer();

        EndDrawing();
    }

    quit();

    return 0;
}