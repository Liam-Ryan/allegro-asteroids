#include "blast.h"

const float BLAST_SPD = 8;
const float BLAST_SIZE = 2;
const unsigned char R = 255;
const unsigned char G = 0;
const unsigned char B = 0;


blast *create_blast(ship *s)
{
	double heading_sin = sin(-s->heading);
	double heading_cos = cos(-s->heading);
	blast *b = malloc(sizeof(blast));
	b->pos = s->pos;
	b->pos.x -= heading_sin * SHIP_WIDTH / 2;
	b->pos.y -= heading_cos * SHIP_HEIGHT / 2;
	b->heading = s->heading;
	b->vel.x = -(float)heading_sin * BLAST_SPD;
	b->vel.y = -(float)heading_cos * BLAST_SPD;
	b->color = al_map_rgb(R, G, B);
	return b;

}

void draw_blast_fn(void *object)
{
	al_draw_filled_circle(0, 0, BLAST_SIZE, ((blast*)object)->color);
	al_draw_rectangle(-BLAST_SIZE, -BLAST_SIZE, BLAST_SIZE, BLAST_SIZE, al_map_rgb(255, 255, 255), 1);
}

int draw_blast(blast *b)
{
	screen_handler_draw(b->pos, b->heading, b, draw_blast_fn);
}

bool move_blast(blast *b, ALLEGRO_DISPLAY_MODE display_data) {
	return screen_handler_move(&b->vel, &b->pos, display_data, false);
}