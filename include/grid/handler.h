#ifndef __STTT_GRID_HANDLER_H
#define __STTT_GRID_HANDLER_H

#include <grid.h>
#include <defs.h>

extern grid_t grid[3][3];
extern grid_t grid_wins;

extern size_t next_grid_x;
extern size_t next_grid_y;

cell_state win_check(grid_t grid);

cell_state handle_input(int mouseX, int mouseY);

#endif /* __STTT_GRID_HANDLER_H */