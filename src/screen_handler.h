#ifndef ALLEGRO_ASTEROIDS_MOVEMENT_HANDLER_H
#define ALLEGRO_ASTEROIDS_MOVEMENT_HANDLER_H
#include "ast_vector.h"
#include <allegro5/allegro.h>

bool screen_handler_move(ast_vector *vel, ast_vector *pos, ALLEGRO_DISPLAY_MODE disp_mode, bool screen_wrap);

void screen_handler_draw(ast_vector pos, double rot, void *object, void (*draw_shape) (void *object));

#endif //ALLEGRO_ASTEROIDS_MOVEMENT_HANDLER_H
