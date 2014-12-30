

#include "draw.h"
//void al_draw_filled_circle(float cx, float cy, float r, ALLEGRO_COLOR color)
void drawObj(Obj * object , double scale){ //piirretään objekti, tätä ei koskaan kutsuta itse
	float x = (float) getVectVal(getObjAttr(object, 'p'), 0);
	float y = (float) getVectVal(getObjAttr(object, 'p'), 1);
	//scale += 100;
	ALLEGRO_COLOR color = al_map_rgb(200,200,200);
	al_draw_filled_circle(320.0+(float)scale*x,240.0+(float)scale*y,10,color);
}
void drawObjList(ObjList * list, double scale){//piirretaan lista, tätä kutsutaan itse.
	for (size_t i=0;i<list->size;i++)
		drawObj(list->obj[i],scale);
}
