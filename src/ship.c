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
const float YAW_INC = .05;
const CIRCLE_RADS = 2 * M_PI;


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
	al_rotate_transform(&transform, s->heading);
	al_translate_transform(&transform, s->pos_x, s->pos_y);
	al_use_transform(&transform);
	al_draw_triangle(0, -y_coord, -x_coord , y_coord , x_coord, y_coord , s->color, SHIP_LINEWIDTH);
}

float clamp_rads( float rads) {
	rads = fmod(rads, CIRCLE_RADS);
	if (rads < 0)
		rads += CIRCLE_RADS;
	return rads;
}

int move_ship(bool forward, bool left, bool right, ship *s, ALLEGRO_DISPLAY_MODE display_data)
{
	if(left) 
		s->heading -= YAW_INC;
	if(right)
		s->heading += YAW_INC;
//	TODO - FIX BUG, JUMPS ONCE PER REVOLUTION
//	s->heading = clamp_rads(s->heading);
	if(forward){
		s->vel_x -= sin(-s->heading) * VEL_INC;
		s->vel_y -= cos(-s->heading) * VEL_INC;
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

	if(s->pos_x > display_data.width) 
		s->pos_x -= display_data.width;
	if(s->pos_x < 0)
		s->pos_x += display_data.width;
	if(s->pos_y < 0) 
		s->pos_y += display_data.height;
	if(s->pos_y > display_data.height)
		s->pos_y -= display_data.height;
	

}
