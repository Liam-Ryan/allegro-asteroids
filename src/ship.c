#include "ship.h"

const float SHIP_HEIGHT = 30;
const float SHIP_WIDTH = 20;
const float SHIP_INITIAL_HEADING = 0;
const float SHIP_LINEWIDTH = 3;
const float VEL_INC = .1;
const float MAX_VEL = 2;
const float YAW_INC = .05;
const double CIRCLE_RADS = 2 * M_PI;


ship *create_ship(float pos_x, float pos_y, ALLEGRO_COLOR color)
{
	ship *s = malloc(sizeof(ship));
	if (!s) {
		fprintf(stderr, "Memory error when creating ship!\n");
	} else {
		s->pos = *ast_create_vector(pos_x, pos_y);
		s->vel = *ast_create_vector(0, 0);
		s->is_dead = false;
		s->heading = SHIP_INITIAL_HEADING;
		s->color = color;
	}
	return s;
}

void draw_ship_fn(void *object)
{
	ship *s = (ship*)object;
	float x_coord = SHIP_WIDTH / 2;
	float y_coord = SHIP_HEIGHT / 2;
	al_draw_triangle(0, -y_coord, -x_coord, y_coord, x_coord, y_coord, s->color, SHIP_LINEWIDTH);
	float cos_heading = (float)cos(s->heading);
	float sin_heading = (float)sin(s->heading);
	x_coord = s->pos.x + x_coord;
	y_coord = s->pos.y + y_coord;
	ALLEGRO_TRANSFORM t;
	al_identity_transform(&t);
	al_rotate_transform(&t, 0);
	al_translate_transform(&t, 0, 0);
	al_use_transform(&t);
	float x1 = cos_heading * (x_coord - s->pos.x) + sin_heading * (y_coord - s->pos.y) + s->pos.x;
	float y1 = sin_heading * (x_coord - s->pos.x) + cos_heading * (y_coord - s->pos.y) + s->pos.y;
	x_coord = s->pos.x - SHIP_WIDTH/2;
	y_coord = s->pos.y - SHIP_HEIGHT/2;
	float x2 = cos_heading * (x_coord - s->pos.x) + sin_heading * (y_coord - s->pos.y) + s->pos.x;
	float y2 = sin_heading * (x_coord - s->pos.x) + cos_heading * (y_coord - s->pos.y) + s->pos.y;
	al_draw_rectangle(x1,y1,x2,y2, al_map_rgb(255, 255, 255), 1);
}

int draw_ship(ship *s)
{
	screen_handler_draw(s->pos, s->heading, s, draw_ship_fn);
}

double clamp_rads(double rads)
{
	rads = fmod(rads, CIRCLE_RADS);
	if (rads < 0)
		rads += CIRCLE_RADS;
	return rads;
}

int move_ship(bool forward, bool left, bool right, ship *s, ALLEGRO_DISPLAY_MODE display_data)
{
	if (left)
		s->heading -= YAW_INC;
	if (right)
		s->heading += YAW_INC;
//	TODO - FIX BUG, JUMPS ONCE PER REVOLUTION
//	s->heading = clamp_rads(s->heading);
	if (forward) {
		s->vel.x -= sin(-s->heading) * VEL_INC;
		s->vel.y -= cos(-s->heading) * VEL_INC;
	}

	if (s->vel.x > MAX_VEL)
		s->vel.x = MAX_VEL;
	if (s->vel.y > MAX_VEL)
		s->vel.y = MAX_VEL;
	if (s->vel.x < -MAX_VEL)
		s->vel.x = -MAX_VEL;
	if (s->vel.y < -MAX_VEL)
		s->vel.y = -MAX_VEL;

	screen_handler_move(&s->vel, &s->pos, display_data, true);

}
