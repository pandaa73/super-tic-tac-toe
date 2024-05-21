#include <grid/drawer.h>
#include <grid/handler.h>

#include <../settings.h>

#include <raylib.h>

Font font;

void draw_big_cell(cell_state cell, size_t x, size_t y) {
    if(cell == CELL_NONE) return;

    DrawRectangle(
        x + GRID_BIG_SPACING,
        y + GRID_BIG_SPACING,
        GRID_BIG_SIZE - 2 * GRID_BIG_SPACING,
        GRID_BIG_SIZE - 2 * GRID_BIG_SPACING,  
        BLACK
    );

    switch(cell) {
        case CELL_X: {
            DrawLineEx(
                (Vector2){
                    x + GRID_BIG_SPACING,
                    y + GRID_BIG_SPACING
                }, 
                (Vector2){
                    x + GRID_BIG_SIZE - GRID_BIG_SPACING,
                    y + GRID_BIG_SIZE - GRID_BIG_SPACING
                },
                GRID_RESULT_THICKNESS, RED
            );

            DrawLineEx(
                (Vector2){
                    x + GRID_BIG_SPACING,
                    y + GRID_BIG_SIZE - GRID_BIG_SPACING
                }, 
                (Vector2){
                    x + GRID_BIG_SIZE - GRID_BIG_SPACING,
                    y + GRID_BIG_SPACING
                },
                GRID_RESULT_THICKNESS, RED
            );

            break;
        }

        case CELL_O: {
            DrawCircle(
                x + GRID_BIG_SIZE / 2,
                y + GRID_BIG_SIZE / 2,
                (GRID_BIG_SIZE - GRID_BIG_SPACING) / 2,
                BLUE
            );

            DrawCircle(
                x + GRID_BIG_SIZE / 2,
                y + GRID_BIG_SIZE / 2,
                (GRID_BIG_SIZE - GRID_BIG_SPACING) / 2 - GRID_RESULT_THICKNESS,
                BLACK
            );

            break;
        }

        case CELL_TIE: {
            DrawLineEx(
                (Vector2){
                    x + GRID_BIG_SPACING,
                    y+ GRID_BIG_SIZE / 2
                }, 
                (Vector2){
                    x + GRID_BIG_SIZE - GRID_BIG_SPACING,
                    y + GRID_BIG_SIZE / 2
                },
                GRID_RESULT_THICKNESS, GRAY
            );

            break;
        }
    }

    return;
}

void draw_small_cell(cell_state cell, size_t x, size_t y) {
    switch(cell) {
        case CELL_X: {
            DrawLineEx(
                (Vector2){
                    x + GRID_SMALL_SPACING,
                    y + GRID_SMALL_SPACING
                }, 
                (Vector2){
                    x + GRID_SMALL_SIZE - GRID_SMALL_SPACING,
                    y + GRID_SMALL_SIZE - GRID_SMALL_SPACING
                },
                GRID_ITEM_THICKNESS, RED
            );

            DrawLineEx(
                (Vector2){
                    x + GRID_SMALL_SPACING,
                    y + GRID_SMALL_SIZE - GRID_SMALL_SPACING
                }, 
                (Vector2){
                    x + GRID_SMALL_SIZE - GRID_SMALL_SPACING,
                    y + GRID_SMALL_SPACING
                },
                GRID_ITEM_THICKNESS, RED
            );

            break;
        }

        case CELL_O: {
            DrawCircle(
                x + GRID_SMALL_SIZE / 2,
                y + GRID_SMALL_SIZE / 2,
                (GRID_SMALL_SIZE - GRID_SMALL_SPACING) / 2,
                BLUE
            );

            DrawCircle(
                x + GRID_SMALL_SIZE / 2,
                y + GRID_SMALL_SIZE / 2,
                (GRID_SMALL_SIZE - GRID_SMALL_SPACING) / 2 
                 - GRID_ITEM_THICKNESS,
                BLACK
            );

            break;
        }
    }

    return;
}

void draw_grid(size_t next_x, size_t next_y) {
    DrawLineEx(
        (Vector2){1 * GRID_BIG_SIZE + GRID_BORDER_X,         0 + GRID_BORDER_Y},
        (Vector2){1 * GRID_BIG_SIZE + GRID_BORDER_X, GRID_SIZE + GRID_BORDER_Y},
        10, WHITE
    );

    DrawLineEx(
        (Vector2){2 * GRID_BIG_SIZE + GRID_BORDER_X,         0 + GRID_BORDER_Y},
        (Vector2){2 * GRID_BIG_SIZE + GRID_BORDER_X, GRID_SIZE + GRID_BORDER_Y},
        10, WHITE
    );

    DrawLineEx(
        (Vector2){        0 + GRID_BORDER_Y, 1 * GRID_BIG_SIZE + GRID_BORDER_X},
        (Vector2){GRID_SIZE + GRID_BORDER_Y, 1 * GRID_BIG_SIZE + GRID_BORDER_X},
        10, WHITE
    );

    DrawLineEx(
        (Vector2){        0 + GRID_BORDER_Y, 2 * GRID_BIG_SIZE + GRID_BORDER_X},
        (Vector2){GRID_SIZE + GRID_BORDER_Y, 2 * GRID_BIG_SIZE + GRID_BORDER_X},
        10, WHITE
    );

    for(size_t i = 0, x = GRID_BORDER_X; i < 3; ++i, x += GRID_BIG_SIZE) {
        for(size_t j = 0, y = GRID_BORDER_Y; j < 3; ++j, y += GRID_BIG_SIZE) {
            DrawLineEx(
                (Vector2){GRID_C2(x), GRID_C1(y)},
                (Vector2){GRID_C2(x), GRID_C4(y)},
                4, WHITE
            );

            DrawLineEx(
                (Vector2){GRID_C3(x), GRID_C1(y)},
                (Vector2){GRID_C3(x), GRID_C4(y)},
                4, WHITE
            );

            DrawLineEx(
                (Vector2){GRID_C1(x), GRID_C2(y)},
                (Vector2){GRID_C4(x), GRID_C2(y)},
                4, WHITE
            );

            DrawLineEx(
                (Vector2){GRID_C1(x), GRID_C3(y)},
                (Vector2){GRID_C4(x), GRID_C3(y)},
                4, WHITE
            );

            for(size_t k = 0, x1 = GRID_BIG_SPACING; k < 3;
               ++k, x1 += GRID_SMALL_SIZE) {
                for(size_t l = 0, y1 = GRID_BIG_SPACING; l < 3;
                   ++l, y1 += GRID_SMALL_SIZE) {
                    draw_small_cell(grid[i][j][k][l], x + x1, y + y1);
                }
            }

            draw_big_cell(grid_wins[i][j], x, y);
        }
    }

    if(next_x == -1 || next_y == -1) {
        DrawRectangleLinesEx(
            (Rectangle){
                GRID_BORDER_X,
                GRID_BORDER_Y,
                GRID_SIZE,
                GRID_SIZE
            }, GRID_BIG_THICKNESS, LIME
        );
    } else {
        DrawRectangleLinesEx(
            (Rectangle){
                GRID_BORDER_X + next_x * GRID_BIG_SIZE,
                GRID_BORDER_Y + next_y * GRID_BIG_SIZE,
                GRID_BIG_SIZE,
                GRID_BIG_SIZE
            }, GRID_BIG_THICKNESS, LIME
        );
    }

    return;
}

void draw_win(cell_state winner) {
    char win_str[16] = " Player # wins ";
    win_str[8] = winner;

    Vector2 text_size = MeasureTextEx(font, win_str, TEXT_FONT_SIZE,
        TEXT_SPACING);

    text_size.y += 20;

    DrawRectangleV(
        (Vector2){
            GRID_BORDER_X + (GRID_SIZE - text_size.x) / 2,
            GRID_BORDER_Y + (GRID_SIZE - text_size.y) / 2 
        },
        text_size, BLACK
    );

    DrawRectangleLinesEx(
        (Rectangle){
            GRID_BORDER_X + (GRID_SIZE - text_size.x) / 2 - GRID_BIG_THICKNESS,
            GRID_BORDER_Y + (GRID_SIZE - text_size.y) / 2 - GRID_BIG_THICKNESS,
            text_size.x + 2 * GRID_BIG_THICKNESS,
            text_size.y + 2 * GRID_BIG_THICKNESS
        },
        GRID_BIG_THICKNESS, YELLOW
    );

    DrawTextEx(
        font, win_str,
        (Vector2){
            GRID_BORDER_X + (GRID_SIZE - text_size.x) / 2,
            GRID_BORDER_Y + (GRID_SIZE - text_size.y) / 2 
        },
        TEXT_FONT_SIZE, TEXT_SPACING, YELLOW
    );
}

void draw_tie(void) {
    char tie_str[25] = " The game ends in a tie ";
    Vector2 text_size = MeasureTextEx(font, tie_str, TEXT_FONT_SIZE,
        TEXT_SPACING);

    text_size.y += 20;

    DrawRectangleV(
        (Vector2){
            GRID_BORDER_X + (GRID_SIZE - text_size.x) / 2,
            GRID_BORDER_Y + (GRID_SIZE - text_size.y) / 2 
        },
        text_size, BLACK
    );

    DrawRectangleLinesEx(
        (Rectangle){
            GRID_BORDER_X + (GRID_SIZE - text_size.x) / 2 - GRID_BIG_THICKNESS,
            GRID_BORDER_Y + (GRID_SIZE - text_size.y) / 2 - GRID_BIG_THICKNESS,
            text_size.x + 2 * GRID_BIG_THICKNESS,
            text_size.y + 2 * GRID_BIG_THICKNESS
        },
        GRID_BIG_THICKNESS, YELLOW
    );

    DrawTextEx(
        font, tie_str,
        (Vector2){
            GRID_BORDER_X + (GRID_SIZE - text_size.x) / 2,
            GRID_BORDER_Y + (GRID_SIZE - text_size.y) / 2 
        },
        TEXT_FONT_SIZE, TEXT_SPACING, YELLOW
    );
}