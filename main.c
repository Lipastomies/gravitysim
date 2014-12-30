#include "draw.h" //fysiikat ja objektien kanssa leikkiminen

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

int rand_lim(int limit) {
/* return a random number between 0 and limit inclusive.
 */

    int divisor = RAND_MAX/(limit+1);
    int retval;

    do {
        retval =1+ rand() / divisor;
    } while (retval > limit );
    return retval ;
}

Vect * randVect(int lim1, int lim2){
	Vect * retval = createVect();
	setVect(retval, (double)rand_lim(lim1), (double)rand_lim(lim2));
	return retval;
}

void initAllegro(){
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();	
}

int main (void){
	initAllegro();
	srand(time(NULL));
	//luodaan näyttö, timerit, muu roska
	//näyttö, event_queue, timeri
	ALLEGRO_DISPLAY * display = al_create_display(640,480);
	ALLEGRO_EVENT_QUEUE * event_queue = NULL;
	ALLEGRO_TIMER * timer = NULL;
	
	//hiiren koordinaatit
	Vect * mouse = createVect();
	
	double FPS = 60;
	timer = al_create_timer(1/FPS);
	event_queue = al_create_event_queue();
	
	al_register_event_source(event_queue, al_get_display_event_source(display)); //display tungetaan event_queueen
	al_register_event_source(event_queue, al_get_timer_event_source(timer));//ajastin tungetaan event_queueen
	al_register_event_source(event_queue, al_get_keyboard_event_source());//näpiskä tungetaan event_queueen
	al_register_event_source(event_queue, al_get_mouse_event_source());
	//itse simuloitavat kappaleet ja niiden luonti
	
	ObjList * list = createObjList();
	for (int i = 0;i<30;i++){//HUOM:n. 200 kappaletta on maksimi
		Obj * temp = createObj((double)rand_lim(500));
		setObjAttr( temp, randVect(640,480), 'p');
		setObjAttr(temp,randVect(100,100),'v');
		multVect( getObjAttr( temp, 'v'),0.02);
		addObj( list,temp);
	}
	
	//loopin toimimiselle olennaisia muuttujia
	int gameover = 0;
	int redraw = 0;
	int pause = 0;
	
	al_clear_to_color(al_map_rgb(0,0,0));
	al_start_timer(timer);
	while (!gameover){//input-looppi, simulaatio ja kaikki muu hyödyllinen
					  //tapahtuu täällä
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = 1;
			//simulointi tänne
			if (!pause){
				updatePos(list);
				updateAcc(list);
				updateVel(list);
			}
		}
					  
		//tähän joku ehto
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
        		gameover = 1;
        	}
        	else if (ev.keyboard.keycode == ALLEGRO_KEY_P){
				if (pause)
					pause = 0;
				else
					pause = 1;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
              ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
         setVect( mouse,(double)ev.mouse.x,(double)ev.mouse.y);
      }
		
		if (redraw && al_is_event_queue_empty(event_queue)){
			if (al_get_timer_count(timer) % 60 == 0)
				printVect(mouse);
			redraw = 0;
			al_clear_to_color(al_map_rgb(0,0,0));
			drawObjList(list, 0.2);
			al_flip_display();
		}
	}
	//siivous
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	destroyObjList(list);
	destroyVect(mouse);
	return 0;
}
