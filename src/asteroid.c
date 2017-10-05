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
		a->pos.y = 0;
		a->pos.x = rnd % display_mode.width + 1;
		break;
	case BOTTOM:
		a->pos.y = display_mode.height;
		a->pos.x = rnd % display_mode.width + 1;
		break;
	case LEFT:
		a->pos.y = rnd % display_mode.height + 1;
		a->pos.x = 0;
		break;
	case RIGHT:
		a->pos.y = rnd % display_mode.height + 1;
		a->pos.x = display_mode.width;
		break;
	}
	a->heading = ((double) rnd / (double) RAND_MAX) * (2 * M_PI + 1);
	a->vel = *ast_create_vector((float)sin(-a->heading) *AST_SPD, (float)cos(-a->heading * AST_SPD));
	a->size = size;
	a->color = color;
	a->is_destroyed = false;
	a->rot_dir = AST_ROT_DIR;
	a->rot_spd = AST_ROT_SPD;
	a->facing = facing;
	return a;

}

void draw_asteroid_fn(void *object)
{
	float x_coord = (AST_WIDTH * ((asteroid*)object)->size) / 2;
	float y_coord = (AST_HEIGHT * ((asteroid*)object)->size) / 2;
	al_draw_rectangle(-x_coord, -y_coord, x_coord, y_coord, ((asteroid*)object)->color, AST_LINEWIDTH);
}

int draw_asteroid(asteroid *a)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, a->facing);
	al_translate_transform(&transform, a->pos.x, a->pos.y);
	al_use_transform(&transform);
	float x_coord = (AST_WIDTH * a->size) / 2;
	float y_coord = (AST_HEIGHT * a->size) / 2;
	al_draw_rectangle(-x_coord, -y_coord, x_coord, y_coord, a->color, AST_LINEWIDTH);

}

int move_asteroid(asteroid *a, ALLEGRO_DISPLAY_MODE display_data)
{
	a->facing += a->rot_dir * a->rot_spd;
	screen_handler_move(&a->vel, &a->pos, display_data, true);
}
