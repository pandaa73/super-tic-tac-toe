#include <game.h>
#include <font.h>
#include <variables.h>

#include <raylib.h>
#include <string.h>

#define END_BORDER_X 15
#define END_BORDER_Y 10

grid_t grid[3][3];
grid_t wins;
size_t count[3][3];

cell_state next_state   = CELL_X;
bool_t next_turn        = 0;
size_t next_x           = -1;
size_t next_y           = -1;

cell_state winner       = CELL_NONE;
size_t wins_x           = 0;
size_t wins_o           = 0;
size_t ties             = 0;

int GRID_SIZE;

int GRID_BIG_SIZE;
int GRID_BIG_THICKNESS;
int GRID_BIG_SPACING;

int GRID_SMALL_SIZE;
int GRID_SMALL_THICKNESS;
int GRID_SMALL_SPACING;

int GRID_BORDER_X;
int GRID_BORDER_Y;

#define GRID_ITEM_THICKNESS     GRID_SMALL_THICKNESS
#define GRID_RESULT_THICKNESS   GRID_BIG_THICKNESS

#define GRID_C0(offset)         (GRID_BIG_SPACING + offset)
#define GRID_C1(offset)         (GRID_C0(offset) + GRID_SMALL_SIZE)
#define GRID_C2(offset)         (GRID_C1(offset) + GRID_SMALL_SIZE)
#define GRID_C3(offset)         (GRID_C2(offset) + GRID_SMALL_SIZE)

void init_game(void) {
    /* NOTE: there are lots of 'magic numbers' here; *
     *        they're just values that look nice.    */

    int width = get_window_width();
    int height = get_window_height();

    GRID_SIZE               = 21 * width / 40;

    GRID_BIG_SIZE           = GRID_SIZE / 3;
    GRID_BIG_THICKNESS      = GRID_BIG_SIZE / 21;
    GRID_BIG_SPACING        = 2 * GRID_BIG_THICKNESS;

    GRID_SMALL_SIZE         = (GRID_BIG_SIZE - 2 * GRID_BIG_SPACING) / 3;
    GRID_SMALL_THICKNESS    = GRID_SMALL_SIZE / 12;
    GRID_SMALL_SPACING      = 2 * GRID_SMALL_THICKNESS;

    GRID_BORDER_X           = (width  - GRID_SIZE) / 2;
    GRID_BORDER_Y           = (height - GRID_SIZE) / 2;
}

void clear_grid(void) {
    memset(grid, 0x00, sizeof(grid));
    memset(wins, 0x00, sizeof(wins));
    memset(count, 0x00, sizeof(count));

    next_state = CELL_X;
    next_turn = 0;
    next_x = -1;
    next_y = -1;

    winner = CELL_NONE;
    wins_x = 0;
    wins_o = 0;
    ties   = 0;
}

cell_state win_check(grid_t grid) {
    if(grid[0][0] != CELL_NONE && grid[0][0] != CELL_TIE &&
       grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2])
        return grid[0][0];

    if(grid[2][0] != CELL_NONE && grid[2][0] != CELL_TIE &&
       grid[2][0] == grid[1][1] && grid[2][0] == grid[0][2])
        return grid[2][0];

    for(size_t i = 0; i < 3; ++i) {
        if(grid[i][0] != CELL_NONE && grid[i][0] != CELL_TIE &&
           grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2])
            return grid[i][0];

        if(grid[0][i] != CELL_NONE && grid[0][i] != CELL_TIE &&
           grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i])
            return grid[0][i];
    }

    return CELL_NONE;
}

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
                (GRID_SMALL_SIZE - 2 * GRID_SMALL_SPACING) / 2
                 + 408 * GRID_ITEM_THICKNESS / 577,     /* thick / ~sqrt(2) */
                BLUE
            );

            DrawCircle(
                x + GRID_SMALL_SIZE / 2,
                y + GRID_SMALL_SIZE / 2,
                (GRID_SMALL_SIZE - 2 * GRID_SMALL_SPACING) / 2
                 + 408 * GRID_ITEM_THICKNESS / 577      /* thick / ~sqrt(2) */
                 - GRID_ITEM_THICKNESS,
                BLACK
            );

            break;
        }
    }
}

void game_event_handler(void) {
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
       mouseX > GRID_BORDER_X && mouseX < GRID_BORDER_X + GRID_SIZE &&
       mouseY > GRID_BORDER_Y && mouseY < GRID_BORDER_Y + GRID_SIZE) {
        int i, j, k, l;

        int x = mouseX - GRID_BORDER_X;
        int y = mouseY - GRID_BORDER_Y;

        i = x / GRID_BIG_SIZE;
        x = x % GRID_BIG_SIZE - GRID_BIG_SPACING;

        j = y / GRID_BIG_SIZE;
        y = y % GRID_BIG_SIZE - GRID_BIG_SPACING;

        if(x > 0 && x < GRID_BIG_SIZE - 2 * GRID_BIG_SPACING &&
           y > 0 && y < GRID_BIG_SIZE - 2 * GRID_BIG_SPACING &&
           (i == next_x || next_x == -1) &&
           (j == next_y || next_y == -1) &&
            !wins[i][j]) {
            k = x / GRID_SMALL_SIZE;
            l = y / GRID_SMALL_SIZE;

            if(!grid[i][j][k][l]) {
               grid[i][j][k][l] = next_state;
               count[i][j]++;

                cell_state win = win_check(grid[i][j]);

                if(win) {
                    wins[i][j] = win;
                    switch(win) {
                        case CELL_X: {
                            wins_x++;
                            break;
                        }

                        case CELL_O: {
                            wins_o++;
                            break;
                        }
                    }

                    winner = win_check(wins);
                    if(wins_x + wins_o + ties == 9) {
                        if(wins_x == wins_o) winner = CELL_TIE;
                        else if(wins_x > wins_o) winner = CELL_X;
                        else winner = CELL_O;
                    }

                } else if(count[i][j] == 9) {
                    wins[i][j] = CELL_TIE;
                    ties++;

                    if(wins_x + wins_o + ties == 9)
                        winner = CELL_TIE;
                }

                if(wins[k][l]) {
                    next_x = -1;
                    next_y = -1;

                } else {
                    next_x = k;
                    next_y = l;
                }

                next_turn = !next_turn;
                next_state = !next_turn * CELL_X + next_turn * CELL_O;    
            }
        }
    }

    if(winner != CELL_NONE) {
        event_handler = game_end_event_handler;
        screen_drawer = game_end_screen_drawer;

        next_x = 3;
        next_y = 3;
    }
}

void game_screen_drawer(void) {
    DrawLineEx(
        (Vector2){1 * GRID_BIG_SIZE + GRID_BORDER_X,         0 + GRID_BORDER_Y},
        (Vector2){1 * GRID_BIG_SIZE + GRID_BORDER_X, GRID_SIZE + GRID_BORDER_Y},
        GRID_BIG_THICKNESS, WHITE
    );

    DrawLineEx(
        (Vector2){2 * GRID_BIG_SIZE + GRID_BORDER_X,         0 + GRID_BORDER_Y},
        (Vector2){2 * GRID_BIG_SIZE + GRID_BORDER_X, GRID_SIZE + GRID_BORDER_Y},
        GRID_BIG_THICKNESS, WHITE
    );

    DrawLineEx(
        (Vector2){        0 + GRID_BORDER_X, 1 * GRID_BIG_SIZE + GRID_BORDER_Y},
        (Vector2){GRID_SIZE + GRID_BORDER_X, 1 * GRID_BIG_SIZE + GRID_BORDER_Y},
        GRID_BIG_THICKNESS, WHITE
    );

    DrawLineEx(
        (Vector2){        0 + GRID_BORDER_X, 2 * GRID_BIG_SIZE + GRID_BORDER_Y},
        (Vector2){GRID_SIZE + GRID_BORDER_X, 2 * GRID_BIG_SIZE + GRID_BORDER_Y},
        GRID_BIG_THICKNESS, WHITE
    );

    for(size_t i = 0, x = GRID_BORDER_X; i < 3; ++i, x += GRID_BIG_SIZE) {
        for(size_t j = 0, y = GRID_BORDER_Y; j < 3; ++j, y += GRID_BIG_SIZE) {
            DrawLineEx(
                (Vector2){GRID_C1(x), GRID_C0(y)},
                (Vector2){GRID_C1(x), GRID_C3(y)},
                GRID_SMALL_THICKNESS, WHITE
            );

            DrawLineEx(
                (Vector2){GRID_C2(x), GRID_C0(y)},
                (Vector2){GRID_C2(x), GRID_C3(y)},
                GRID_SMALL_THICKNESS, WHITE
            );

            DrawLineEx(
                (Vector2){GRID_C0(x), GRID_C1(y)},
                (Vector2){GRID_C3(x), GRID_C1(y)},
                GRID_SMALL_THICKNESS, WHITE
            );

            DrawLineEx(
                (Vector2){GRID_C0(x), GRID_C2(y)},
                (Vector2){GRID_C3(x), GRID_C2(y)},
                GRID_SMALL_THICKNESS, WHITE
            );

            for(size_t k = 0, x1 = GRID_BIG_SPACING; k < 3;
               ++k, x1 += GRID_SMALL_SIZE) {
                for(size_t l = 0, y1 = GRID_BIG_SPACING; l < 3;
                   ++l, y1 += GRID_SMALL_SIZE) {
                    draw_small_cell(grid[i][j][k][l], x + x1, y + y1);
                }
            }

            draw_big_cell(wins[i][j], x, y);
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
    } else if(next_x < 3 && next_y < 3) {
        DrawRectangleLinesEx(
            (Rectangle){
                GRID_BORDER_X + next_x * GRID_BIG_SIZE,
                GRID_BORDER_Y + next_y * GRID_BIG_SIZE,
                GRID_BIG_SIZE,
                GRID_BIG_SIZE
            }, GRID_BIG_THICKNESS, LIME
        );
    }
}

void game_end_event_handler(void) {
    if(IsKeyPressed(KEY_ENTER)) {
        clear_grid();

        event_handler = game_event_handler;
        screen_drawer = game_screen_drawer;
    }
}

void game_end_screen_drawer(void) {
    game_screen_drawer();

    char tie_str[] = "THE GAME ENDS IN A DRAW";
    char win_str[] = "PLAYER # WINS";
    win_str[7] = winner + 'A' - 'a';

    const char *end_str = (winner == CELL_TIE ? tie_str : win_str);

    Vector2 text_size = measure_text(end_str, FONTSZ_DEFAULT,
        -1, -1);

    text_size.x += 2 * END_BORDER_X;
    text_size.y += 2 * END_BORDER_Y;

    DrawRectangleV(
        (Vector2){
            GRID_BORDER_X + (GRID_SIZE - text_size.x) / 2 - END_BORDER_X,
            GRID_BORDER_Y + (GRID_SIZE - text_size.y) / 2 - END_BORDER_Y
        },
        text_size, BLACK
    );

    DrawRectangleLinesEx(
        (Rectangle){
            GRID_BORDER_X + (GRID_SIZE - text_size.x) / 2
            - GRID_BIG_THICKNESS - END_BORDER_X,
            GRID_BORDER_Y + (GRID_SIZE - text_size.y) / 2
            - GRID_BIG_THICKNESS - END_BORDER_Y,
            text_size.x + 2 * GRID_BIG_THICKNESS,
            text_size.y + 2 * GRID_BIG_THICKNESS
        },
        GRID_BIG_THICKNESS, YELLOW
    );

    draw_text(
        end_str,
        GRID_BORDER_X + (GRID_SIZE - text_size.x) / 2,
        GRID_BORDER_Y + (GRID_SIZE - text_size.y) / 2,
        FONTSZ_DEFAULT, -1, -1, YELLOW
    );
}