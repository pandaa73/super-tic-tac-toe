#include <variables.h>
#include <main_menu.h>
#include <font.h>
#include <../settings.h>

#include <raylib.h>

int main(void) {
    // SetTraceLogLevel(LOG_WARNING);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Super Tic-Tac-Toe!");

    if(!IsWindowReady()) TraceLog(LOG_FATAL, "Failed to created window.");

    font = LoadFontEx("./assets/font.ttf", 360, NULL, 0);
    if(!IsFontReady(font)) TraceLog(LOG_FATAL, "Failed to load font.");

    init_main_menu();
    init_font();

    while(!WindowShouldClose()) {
        ClearBackground(BLACK);

        event_handler();

        BeginDrawing();
            screen_drawer();

        EndDrawing();
    }

    UnloadFont(font);
    CloseWindow();

    return 0;
}