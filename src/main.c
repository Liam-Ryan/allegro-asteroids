#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "ship.h"

const float FPS = 60;
enum KEYS {
	KEY_UP, KEY_LEFT, KEY_RIGHT
};

int main(int argc, char **argv) {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_DISPLAY_MODE disp_data;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_TRANSFORM transform;

	bool key[3] = {false, false, false};
	bool redraw = true;

       	

	if(!al_init() || !al_init_image_addon() || !al_init_primitives_addon() || !al_install_keyboard()) {
		fprintf(stderr, "Failed to initialize allegro!\n");
		goto error_state;
	}

	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

//	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(disp_data.width, disp_data.height);
	if(!display) {
		fprintf(stderr, "Failed to create display");
		goto error_state;
	}

	ship *s = create_ship(disp_data.width / 2.0, disp_data.height / 2.0, 0, al_map_rgb(122, 122, 122));

	timer = al_create_timer (1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "Failed to create timer!\n");
		goto error_destroy_display;
	}
	
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "Failed to create event queue!\n");
		goto error_destroy_timer;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();
	al_start_timer(timer);

	while(1) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		switch(ev.type) {
		case ALLEGRO_EVENT_TIMER:
			redraw = true;
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE: 
			goto clean_exit;
		case ALLEGRO_EVENT_KEY_DOWN:
			switch(ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;	
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;	
			}
			break;	
		case ALLEGRO_EVENT_KEY_UP:
			switch(ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;	
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;	
			}
			break;	

		}

		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			ship_move(key[KEY_UP], key[KEY_LEFT], key[KEY_RIGHT], s);
			al_clear_to_color(al_map_rgb(0,0,0));
			draw_ship(transform, s);
			al_flip_display();
		}
		
	}

clean_exit:
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;

	/**Error exits **/
error_destroy_event_queue:
	al_destroy_event_queue(event_queue);
error_destroy_timer:
	al_destroy_timer(timer);
error_destroy_display:
	al_destroy_display(display);
error_state:
	return -1;

}
