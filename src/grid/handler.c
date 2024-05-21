#include <grid/handler.h>

#include <../settings.h>

grid_t grid[3][3];
grid_t grid_wins;
size_t grid_count[3][3];

cell_state next_state = CELL_X;
bool_t next_turn = 0;
size_t next_grid_x = -1;
size_t next_grid_y = -1;

size_t grid_wins_x = 0;
size_t grid_wins_o = 0;
size_t grid_ties   = 0;

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

cell_state handle_input(int mouseX, int mouseY) {
    cell_state ret = CELL_NONE;

    if(mouseX > GRID_BORDER_X && mouseX < GRID_BORDER_X + GRID_SIZE &&
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
           (i == next_grid_x || next_grid_x == -1) &&
           (j == next_grid_y || next_grid_y == -1) &&
            !grid_wins[i][j]) {
            k = x / GRID_SMALL_SIZE;
            l = y / GRID_SMALL_SIZE;

            if(!grid[i][j][k][l]) {
               grid[i][j][k][l] = next_state;
               grid_count[i][j]++;

                cell_state win = win_check(grid[i][j]);

                if(win) {
                    grid_wins[i][j] = win;
                    switch(win) {
                        case CELL_X: {
                            grid_wins_x++;
                            break;
                        }

                        case CELL_O: {
                            grid_wins_o++;
                            break;
                        }
                    }

                    ret = win_check(grid_wins);
                    if(grid_wins_x + grid_wins_o + grid_ties == 9) {
                        if(grid_wins_x == grid_wins_o) ret = CELL_TIE;
                        else if(grid_wins_x > grid_wins_o) ret = CELL_X;
                        else ret = CELL_O;
                    }

                } else if(grid_count[i][j] == 9) {
                    grid_wins[i][j] = CELL_TIE;
                    grid_ties++;

                    if(grid_wins_x + grid_wins_o + grid_ties == 9) {
                        if(grid_wins_x == grid_wins_o) ret = CELL_TIE;
                        else if(grid_wins_x > grid_wins_o) ret = CELL_X;
                        else ret = CELL_O;
                    }
                }

                if(grid_wins[k][l]) {
                    next_grid_x = -1;
                    next_grid_y = -1;

                } else {
                    next_grid_x = k;
                    next_grid_y = l;
                }

                next_turn = !next_turn;
                next_state = !next_turn * CELL_X + next_turn * CELL_O;    
            }
        }
    }

    if(ret != CELL_NONE) {
        next_grid_x = -1;
        next_grid_y = -1;
    }

    return ret;
}