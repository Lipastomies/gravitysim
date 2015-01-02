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
void normalizeMouse (Vect * retval, Vect * mouse, Vect * pan, double scale){
	double x = getVectVal(mouse,0);
	double y = getVectVal(mouse,1);
	double deltax = getVectVal(pan,0);
	double deltay = getVectVal(pan,1);
	//deskaalaus
	
	x = panVal(x,-deltax);
	y = panVal(y,-deltay);
	x = scaleVal(x,1/scale);
	y = scaleVal(y,1/scale);
	//depanning
	
	setVect(retval,x,y);
}

Vect * randVect(int lim1, int lim2){
	Vect * retval = createVect();
	int temp1=rand_lim(lim1);
	int temp2=rand_lim(lim2);
	if (rand_lim(1000) <= 500)
		temp1 *= -1;
	if (rand_lim(1000) <= 500)
		temp2 *= -1;
	setVect(retval, (double)temp1, (double)temp2);	
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
	Vect * mouse_norm = createVect();
	Vect * pan = createVect();
	setVect( pan, 320,240);
	
	double FPS = 60;
	timer = al_create_timer(1/FPS);
	event_queue = al_create_event_queue();
	
	al_register_event_source(event_queue, al_get_display_event_source(display)); //display tungetaan event_queueen
	al_register_event_source(event_queue, al_get_timer_event_source(timer));//ajastin tungetaan event_queueen
	al_register_event_source(event_queue, al_get_keyboard_event_source());//näpiskä tungetaan event_queueen
	al_register_event_source(event_queue, al_get_mouse_event_source());
	//itse simuloitavat kappaleet ja niiden luonti
	
	ObjList * list = createObjList();
	for (int i = 0;i<10;i++){//HUOM:n. 200 kappaletta on maksimi, mitä jaksetaan pyörittää
		Obj * temp = createObj((double)rand_lim(500));
		Vect * temp1 = randVect(2000,1500);
		Vect * temp2 = randVect(100,100);
		setObjAttr( temp, temp1, 'p');
		setObjAttr(temp,temp2,'v');
		multVect( getObjAttr( temp, 'v'),0.0005);
		addObj( list,temp);
		destroyVect(temp1);
		destroyVect(temp2);
	}
	
	//loopin toimimiselle olennaisia muuttujia, nämä voisi sinänsä 
	//laittaa omaan structiinsa tai johonkin, etteivät ne
	//ole näin sotkuisesti. Tällöin niiden lataaminen tiedostosta
	//saattaisi olla helpompaa.
	int gameover = 0;
	int redraw = 0;
	int pause = 1;
	int forcetoggle = 1; //1 =inverse linear, 2 = inverse square, 3 = softer inverse square
	int timescale = 1;
	double scale = 1;
	
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
				for (int i=0;i<timescale;i++){
					updatePos(list);
					updateAcc(list,forcetoggle);
					updateVel(list);
				}
			}
		}
					  
		//input tässä
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
			else if (ev.keyboard.keycode == ALLEGRO_KEY_O){
        		scale = scale*sqrt(0.5);
        	}
        	else if (ev.keyboard.keycode == ALLEGRO_KEY_I){
        		scale = scale*sqrt(2);
        	}
        	else if (ev.keyboard.keycode == ALLEGRO_KEY_K){
        		timescale++;
        	}
        	else if (ev.keyboard.keycode == ALLEGRO_KEY_J){
        		if (timescale > 1)
					timescale--;
        	}
        	else if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT){
        		setVect(pan, getVectVal(pan,0)+50/scale, getVectVal(pan,1)) ;
        	}
        	else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT){
        		setVect(pan, getVectVal(pan,0)-50/scale, getVectVal(pan,1)) ;
        	}
        	else if (ev.keyboard.keycode == ALLEGRO_KEY_UP){
        		setVect(pan, getVectVal(pan,0), getVectVal(pan,1)+50/scale) ;
        	}
        	else if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN){
        		setVect(pan, getVectVal(pan,0), getVectVal(pan,1)-50/scale) ;
        	}
        	
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
              ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
         setVect( mouse,(double)ev.mouse.x,(double)ev.mouse.y);
         normalizeMouse(mouse_norm,mouse,pan,scale);
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			Obj * temp = createObj((double)rand_lim(500));
			Vect * temp1 = createVect();
			setVect( temp1, getVectVal(mouse_norm,0)-320,getVectVal(mouse_norm,1)-240);
			setObjAttr( temp, temp1,'p'); 
			addObj(list,temp);
			destroyVect(temp1);
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         gameover = 1;
      }
		if (redraw && al_is_event_queue_empty(event_queue)){
			if (al_get_timer_count(timer) % 60 == 0){
				
				printVect(mouse_norm);
				printf("top lel joku pan:");
				printVect(pan);
				printf("top lel joku mouse:");
				printVect(mouse);
				printf("asdasd scale : %lf\n",scale);
			}
			redraw = 0;
			al_clear_to_color(al_map_rgb(0,0,0));
			drawObjList(list, scale, pan);
			al_draw_filled_circle(320,240,2,al_map_rgb(255,0,0));
			al_flip_display();
		}
	}
	//siivous
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	destroyObjList(list);
	destroyVect(mouse);
	destroyVect(mouse_norm);
	destroyVect(pan);
	return 0;
}
