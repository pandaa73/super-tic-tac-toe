#ifndef __STTT_GAME_H
#define __STTT_GAME_H

#include <defs.h>
#include <../settings.h>

#define GRID_BIG_SIZE           (GRID_SIZE / 3)
#define GRID_SMALL_SIZE         ((GRID_BIG_SIZE - 2 * GRID_BIG_SPACING) / 3)
#define GRID_BORDER_X           ((WINDOW_WIDTH - GRID_SIZE) / 2)
#define GRID_BORDER_Y           ((WINDOW_HEIGHT - GRID_SIZE) / 2)

#define GRID_C1(offset)         (GRID_BIG_SPACING + offset)
#define GRID_C2(offset)         (GRID_C1(offset) + GRID_SMALL_SIZE)
#define GRID_C3(offset)         (GRID_C2(offset) + GRID_SMALL_SIZE)
#define GRID_C4(offset)         (GRID_C3(offset) + GRID_SMALL_SIZE)

typedef enum {
    CELL_NONE = 0x00, // null
    CELL_X    = 0x78, // 'x'
    CELL_O    = 0x6f, // 'o'
    CELL_TIE  = 0x2d  // '-'
} cell_state;

typedef cell_state grid_t[3][3];

void game_event_handler(void);
void game_screen_drawer(void);

void game_end_event_handler(void);
void game_end_screen_drawer(void);

#endif /* __STTT_GAME_H */