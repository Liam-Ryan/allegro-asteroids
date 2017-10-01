#ifndef ASTEROID_H
#define ASTEROID_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
typedef struct asteroid {
	float pos_x;
	float pos_y;
	float heading;
	float spd;
	float rot_dir;
	float rot_spd;
	float size;
	float facing;
	bool is_destroyed;
	ALLEGRO_COLOR color;
} asteroid;

asteroid *create_asteroid(float pos_x, float pos_y, float heading, float scale, float facing, ALLEGRO_COLOR color);

int draw_asteroid(ALLEGRO_TRANSFORM transform, asteroid *a);

int move_asteroid(asteroid *a);

#endif
