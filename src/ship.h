#ifndef SHIP_H
#define SHIP_H

#include "ast_vector.h"
#include <math.h>
#include <allegro5/allegro.h>

extern const float
	SHIP_HEIGHT,
	SHIP_WIDTH,
	SHIP_LINEWIDTH;

typedef struct ship {
	ast_vector pos;
	ast_vector vel;
	double heading;
	bool is_dead;
	ALLEGRO_COLOR color;
} ship;

ship *create_ship(float pos_x, float pos_y, ALLEGRO_COLOR color);

int draw_ship(ship *s);

int move_ship(bool forward, bool left, bool right, ship *s, ALLEGRO_DISPLAY_MODE display_data);

#endif
