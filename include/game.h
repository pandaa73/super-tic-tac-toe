#ifndef __STTT_GAME_H
#define __STTT_GAME_H

#include <defs.h>
#include <settings.h>

typedef enum {
    CELL_NONE = 0x00, // null
    CELL_X    = 0x78, // 'x'
    CELL_O    = 0x6f, // 'o'
    CELL_TIE  = 0x2d  // '-'
} cell_state;

typedef cell_state grid_t[3][3];

void init_game(void);
void game_event_handler(void);
void game_screen_drawer(void);

void game_end_event_handler(void);
void game_end_screen_drawer(void);

#endif /* __STTT_GAME_H */