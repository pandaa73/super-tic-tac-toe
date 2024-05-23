#include <variables.h>
#include <main_menu.h>
#include <game.h>

Font font;

event_handler_t event_handler = game_event_handler;
screen_drawer_t screen_drawer = game_screen_drawer;