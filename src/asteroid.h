#ifndef ASTEROID_H
#define ASTEROID_H

#include "screen_handler.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "ast_vector.h"

typedef struct asteroid {
	ast_vector pos;
	ast_vector vel;
	double heading;
	float rot_dir;
	float rot_spd;
	float size;
	float facing;
	bool is_destroyed;
	ALLEGRO_COLOR color;
} asteroid;

asteroid *create_asteroid(ALLEGRO_DISPLAY_MODE display_mode, float scale, float facing, ALLEGRO_COLOR color);

int draw_asteroid(asteroid *a);

int move_asteroid(asteroid *a, ALLEGRO_DISPLAY_MODE display_mode);

#endif
