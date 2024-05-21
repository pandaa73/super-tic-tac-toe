#ifndef __STTT_GRID_DRAWER_H
#define __STTT_GRID_DRAWER_H

#include <grid.h>
#include <defs.h>
#include <raylib.h>

extern Font font;

void draw_big_cell(cell_state cell, size_t x, size_t y);
void draw_small_cell(cell_state cell, size_t x, size_t y);
void draw_grid(size_t next_x, size_t next_y);

void draw_win(cell_state winner);
void draw_tie(void);

#endif /* __STTT_GRID_DRAWER_H */