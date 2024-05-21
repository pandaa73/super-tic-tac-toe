#include <grid/handler.h>
#include <grid/drawer.h>
#include <defs.h>

#include <../settings.h>

#include <raylib.h>

int main(void) {
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Super Tic-Tac-Toe!");

    if(!IsWindowReady()) TraceLog(LOG_FATAL, "Failed to created window.");

    font = LoadFontEx("./assets/font.ttf", 360, NULL, 0);
    if(!IsFontReady(font)) TraceLog(LOG_FATAL, "Failed to load font.");

    cell_state winner = CELL_NONE;
    while(!WindowShouldClose()) {
        ClearBackground(BLACK);
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();

        if(winner == CELL_NONE && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            winner = handle_input(mouseX, mouseY);

        BeginDrawing();
            draw_grid(next_grid_x, next_grid_y);

            if(winner == CELL_TIE) draw_tie();
            else if(winner != CELL_NONE) draw_win(winner);
            
        EndDrawing();
    }

    UnloadFont(font);
    CloseWindow();

    return 0;
}