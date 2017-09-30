#ifndef SHIP_H
#define SHIP_H
#include <math.h>
#include <allegro5/allegro.h>
#define RADIANS(x) (x * M_PI / 180.0)
#define DEGREES(x) (x * 180.0 / M_PI)

extern const float 
	SHIP_HEIGHT,
	SHIP_WIDTH, 
	SHIP_HEADING_INITIAL,
	SHIP_LINEWIDTH,
	SHIP_RED,
	SHIP_GREEN,
	SHIP_BLUE;

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

int draw_ship(ALLEGRO_TRANSFORM transform, ship *s);

int ship_move(bool forward, bool left, bool right, ship *s);

#endif
