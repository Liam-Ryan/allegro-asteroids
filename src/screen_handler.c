#include "screen_handler.h"

bool screen_handler_move(ast_vector *vel, ast_vector *pos, ALLEGRO_DISPLAY_MODE display_data, bool screen_wrap)
{
	ast_add_vector(vel, pos);
	if(screen_wrap) {
		if (pos->x > display_data.width)
			pos->x -= display_data.width;
		if (pos->x < 0)
			pos->x += display_data.width;
		if (pos->y < 0)
			pos->y += display_data.height;
		if (pos->y > display_data.height)
			pos->y -= display_data.height;
	} else{
		if( pos->x > display_data.width || pos->x < 0 || pos->y < 0 || pos->y > display_data.height)
			return false;
	}
	return true;
}

void screen_handler_draw(ast_vector pos, double rot, void *object, void (*draw_shape) (void *object))
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, (float) rot);
	al_translate_transform(&transform, pos.x, pos.y);
	al_use_transform(&transform);
	draw_shape(object);
}