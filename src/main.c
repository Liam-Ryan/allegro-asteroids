#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
 

int main(int argc, char **argv) {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_DISPLAY_MODE disp_data;

	if(!al_init() || !al_init_image_addon() || !al_init_primitives_addon()) {
		fprintf(stderr, "Failed to initialize allegro!\n");
		return -1;
	}

	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(disp_data.width, disp_data.height);
	if(!display) {
		fprintf(stderr, "Failed to create display");
		return -1;
	}
	
	al_rest(2.0);
	al_destroy_display(display);
	return 0;
}
