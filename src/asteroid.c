#include "asteroid.h"

const unsigned int AST_ROT_DIR = 1;
const float AST_ROT_SPD = .04;
const float AST_SPD = 1.2;
const float AST_HEIGHT = 30;
const float AST_WIDTH = 30;
const float AST_LINEWIDTH = 2.4;

enum spawn_sides {
	TOP, BOTTOM, LEFT, RIGHT
};

asteroid *create_asteroid(ALLEGRO_DISPLAY_MODE display_mode, float size, float facing, ALLEGRO_COLOR color)
{

	asteroid *a = malloc(sizeof(asteroid));
	int rnd = rand();
	int spawn_side = rnd % 4;
	switch (spawn_side) {
	case TOP:
		a->pos_y = 0;
		a->pos_x = rnd % display_mode.width + 1;
		break;
	case BOTTOM:
		a->pos_y = display_mode.height;
		a->pos_x = rnd % display_mode.width + 1;
		break;
	case LEFT:
		a->pos_y = rnd % display_mode.height + 1;
		a->pos_x = 0;
		break;
	case RIGHT:
		a->pos_y = rnd % display_mode.height + 1;
		a->pos_x = display_mode.width;
		break;
	}
	a->heading = ((double) rnd / (double) RAND_MAX) * (2 * M_PI + 1);
	a->spd = AST_SPD;
	a->size = size;
	a->color = color;
	a->is_destroyed = false;
	a->rot_dir = AST_ROT_DIR;
	a->rot_spd = AST_ROT_SPD;
	a->facing = facing;
	return a;

}

int draw_asteroid(asteroid *a)
{
	ALLEGRO_TRANSFORM transform;
	float x_coord = (AST_WIDTH * a->size) / 2;
	float y_coord = (AST_HEIGHT * a->size) / 2;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, a->facing);
	al_translate_transform(&transform, (float) a->pos_x, (float) a->pos_y);
	al_use_transform(&transform);
	al_draw_rectangle(-x_coord, -y_coord, x_coord, y_coord, a->color, AST_LINEWIDTH);

}

int move_asteroid(asteroid *a, ALLEGRO_DISPLAY_MODE display_data)
{
	a->facing += a->rot_dir * a->rot_spd;
	a->pos_x -= sin(-a->heading) * a->spd;
	a->pos_y -= cos(-a->heading) * a->spd;
	if (a->pos_x < 0)
		a->pos_x += display_data.width;
	if (a->pos_x > display_data.width)
		a->pos_x -= display_data.width;
	if (a->pos_y < 0)
		a->pos_y += display_data.height;
	if (a->pos_y > display_data.height)
		a->pos_y -= display_data.height;
}
