#include "ship.h"
#include <stdio.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

const float SHIP_HEIGHT = 30;
const float SHIP_WIDTH = 20;
const float SHIP_INITIAL_HEADING = 0;
const float SHIP_LINEWIDTH = 3;
const float VEL_INC = .1;
const float MAX_VEL = 2;
const float YAW_INC = 1;



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
		s->heading = SHIP_INITIAL_HEADING;
		s->color = color;
	}
	return s;
}

int draw_ship(ALLEGRO_TRANSFORM transform, ship *s)
{
	float x_coord = SHIP_WIDTH / 2;
	float y_coord = SHIP_HEIGHT / 2;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, RADIANS(s->heading));
	al_translate_transform(&transform, s->pos_x, s->pos_y);
	al_use_transform(&transform);
	al_draw_triangle( -x_coord , y_coord , 0, -y_coord, x_coord, y_coord , s->color, SHIP_LINEWIDTH);
}

int ship_move(bool forward, bool left, bool right, ship *s)
{
	if(left) 
		s->heading -= YAW_INC;
	if(right)
		s->heading += YAW_INC;


	if(s->heading < 0)
	       s->heading += 360;	
	if(s->heading > 359)
		s->heading -= 360;
	if(forward){
		s->vel_x += cos(RADIANS(s->heading));
		s->vel_y += sin(RADIANS(s->heading));
	}
	if(s->vel_x > MAX_VEL)
		s->vel_x = MAX_VEL;
	if(s->vel_y > MAX_VEL)
		s->vel_y = MAX_VEL;	
	if(s->vel_x < -MAX_VEL)
		s->vel_x = -MAX_VEL;	
	if(s->vel_y < -MAX_VEL)
		s->vel_y = -MAX_VEL;	
	
	s->pos_x += s->vel_x;
	s->pos_y += s->vel_y;
}
