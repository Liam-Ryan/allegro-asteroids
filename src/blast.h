#ifndef ALLEGRO_ASTEROIDS_BLAST_H
#define ALLEGRO_ASTEROIDS_BLAST_H

#include "ast_vector.h"
#include "ship.h"
#include <stdbool.h>
#include <allegro5/allegro.h>
typedef struct blast {
	ast_vector pos;
	ast_vector vel;
	double heading;
	bool off_screen;
	ALLEGRO_COLOR color;
} blast;

blast *create_blast(ship *s);

int draw_blast(blast *b);

bool move_blast(blast *b, ALLEGRO_DISPLAY_MODE display_data);


#endif //ALLEGRO_ASTEROIDS_BLAST_H
