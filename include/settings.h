#ifndef __STTT_SETTINGS_H
#define __STTT_SETTINGS_H

#include <defs.h>

typedef struct {
    int version;
    int size;

    size_t resolution;

} settings_t;

void init_settings(void);
void settings_event_handler(void);
void settings_screen_drawer(void);

void save_settings(void);
void load_settings(void);
void load_settings_default(void);

int get_window_width(void);
int get_window_height(void);

#endif /* __STTT_SETTINGS_H */