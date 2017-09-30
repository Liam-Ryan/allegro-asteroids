#include <allegro5/allegro.h>

typedef struct ship{
	float pos_x;
	float pos_y;
	float vel_x;
	float vel_y;
	float heading;
	bool isDead;
	ALLEGRO_COLOR color;
} ship;

ship *create_ship(float pos_x, float pos_y, float heading, ALLEGRO_COLOR color);

int draw_ship(ship *s); 
