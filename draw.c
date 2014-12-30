

#include "draw.h"
//void al_draw_filled_circle(float cx, float cy, float r, ALLEGRO_COLOR color)
void drawObj(Obj * object , double scale, Vect* pan){ //piirretään objekti, tätä ei koskaan kutsuta itse
	float x = (float) getVectVal(getObjAttr(object, 'p'), 0);
	float y = (float) getVectVal(getObjAttr(object, 'p'), 1);
	ALLEGRO_COLOR color = al_map_rgb(200,200,200);
	float deltax = 320;
	float deltay = 240;
	if (pan != NULL){
		deltax = getVectVal(pan,0);
		deltay = getVectVal(pan,1);
	}
	al_draw_filled_circle(deltax+(float)scale*x,deltay+(float)scale*y,4,color);
}
void drawObjList(ObjList * list, double scale, Vect * pan){//piirretaan lista, tätä kutsutaan itse.
	for (size_t i=0;i<list->size;i++)
		drawObj(list->obj[i],scale, pan);
}
