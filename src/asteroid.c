#include "asteroid.h"

const unsigned int AST_ROT_DIR = 1;
const float AST_ROT_SPD = .04;
const float AST_SPD = 1.2;
const float AST_HEIGHT = 30;
const float AST_WIDTH = 30;
const float AST_LINEWIDTH = 2.4;

asteroid *create_asteroid(float pos_x, float pos_y, float heading, float size,float facing, ALLEGRO_COLOR color)
{
	asteroid *a = malloc(sizeof(asteroid));
	a->pos_x = pos_x;
	a->pos_y = pos_y;
	a->heading = heading;
	a->spd = AST_SPD;
	a->size = size;
	a->color = color;
	a->is_destroyed = false;
	a->rot_dir = AST_ROT_DIR;
	a->rot_spd = AST_ROT_SPD;
	a->facing = facing;
	return a;

}

int draw_asteroid(ALLEGRO_TRANSFORM transform, asteroid *a){
	float x_coord = (AST_WIDTH * a->size) / 2;
	float y_coord = (AST_HEIGHT * a->size) / 2;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, a->facing); 
	al_translate_transform(&transform, a->pos_x, a->pos_y);
	al_use_transform(&transform); 
	al_draw_rectangle(-x_coord, -y_coord, x_coord, y_coord, a->color, AST_LINEWIDTH);

}

int move_asteroid(asteroid *a) {
	a->facing += a->rot_dir * a->rot_spd;
	a->pos_x -= sin(-a->heading) * a->spd;
	a->pos_y -= cos(-a->heading) * a->spd;
}
