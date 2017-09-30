#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "ship.h"

#define DEGREE(x) ((x) * ((180.0) / (M_PI)))  

const float FPS = 60;
const float BOUNCER_SIZE = 32;

int main(int argc, char **argv) {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_DISPLAY_MODE disp_data;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	ALLEGRO_TRANSFORM transform;
	float bouncer_x = 0;
	float bouncer_y = 0;
	float bouncer_dir_x = -4.0;
	float bouncer_dir_y = 4.0;
	bool redraw = true;

       	

	if(!al_init() || !al_init_image_addon() || !al_init_primitives_addon() || !al_install_mouse()) {
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

	bouncer_x = disp_data.width / 2.0 - BOUNCER_SIZE / 2.0;
	bouncer_y = disp_data.height / 2.0 - BOUNCER_SIZE / 2.0;

	bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
	if(!bouncer) {
		fprintf(stderr, "Failed to create bitmap!\n");
		goto error_destroy_display;
	}

	ship *s = create_ship(disp_data.width / 2.0, disp_data.height / 2.0, 0, al_map_rgb(122, 122, 122));

	al_set_target_bitmap(bouncer);
	al_clear_to_color(al_map_rgb(255,0,255));
	al_set_target_bitmap(al_get_backbuffer(display));

	timer = al_create_timer (1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "Failed to create timer!\n");
		goto error_destroy_bouncer;
	}
	
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "Failed to create event queue!\n");
		goto error_destroy_timer;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();
	al_start_timer(timer);

	while(1) {
		ALLEGRO_EVENT ev;

		al_wait_for_event(event_queue, &ev);

		switch(ev.type) {
		case ALLEGRO_EVENT_TIMER:
		//	if(bouncer_x < 0 || bouncer_x > disp_data.width - BOUNCER_SIZE) 
		//		bouncer_dir_x = -bouncer_dir_x;
		//	if(bouncer_y < 0 || bouncer_y > disp_data.height - BOUNCER_SIZE)
		//		bouncer_dir_y = -bouncer_dir_y;
			
		//	bouncer_x += bouncer_dir_x;
		//	bouncer_y += bouncer_dir_y;
		//		draw_ship(&ship_transform, s);



			redraw = true;
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE: 
			goto clean_exit;
		case ALLEGRO_EVENT_MOUSE_AXES:
		case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
			bouncer_x = ev.mouse.x;
			bouncer_y = ev.mouse.y;
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			goto clean_exit;
		}

		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0,0,0));
		         al_draw_triangle( -10 , 0 , 10, 0 , 0 , -30, s->color, 3.0f);

		         al_identity_transform(&transform);
		         al_rotate_transform(&transform, DEGREE(s->heading));
		         al_translate_transform(&transform, s->pos_x, s->pos_y);
		         al_use_transform(&transform);
		         //al_draw_triangle( -10 , 0 , 10, 0 , 0 , -30, s->color, 3.0f);
			 
		         //al_draw_triangle( s->pos_x , s->pos_y , s->pos_x, s->pos_y , s->pos_x , s->pos_y, s->color, 3.0f);

			al_flip_display();
		}
		
	}

clean_exit:
	al_destroy_bitmap(bouncer);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;

	/**Error exits **/
error_destroy_event_queue:
	al_destroy_event_queue(event_queue);
error_destroy_timer:
	al_destroy_timer(timer);
error_destroy_bouncer:
	al_destroy_bitmap(bouncer);
error_destroy_display:
	al_destroy_display(display);
error_state:
	return -1;

}
