#include "ship.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

ship *create_ship(float pos_x, float pos_y, float heading, ALLEGRO_COLOR color)
{
	ship *s = malloc(sizeof(ship));
	if(!s) {
		fprintf(stderr, "Memory error when creating ship!\n");
	} else { 
		s->pos_x = pos_x;
		s->pos_y = pos_y;
		s->vel_x = 0;
		s->vel_y = 0;
	       	s->isDead = false;
		s->heading = heading;
		s->color = color;
	}
	return s;
}

int draw_ship(ship *s)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, s->heading);
	al_translate_transform(&transform, s->pos_x, s->pos_y);
	al_use_transform(&transform);
	al_draw_triangle( s->pos_x -2, s->pos_y -2, s->pos_x, s->pos_y + 4, s->pos_x + 2, s->pos_y +2, s->color, 3.0f);
}
