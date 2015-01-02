

#include "draw.h"


//void al_draw_filled_circle(float cx, float cy, float r, ALLEGRO_COLOR color)

double scaleVal(double val, double scale){
	return scale*val;
}
double panVal(double val, double pan){
	return pan + val;
}
void drawObj(Obj * object , double scale, Vect* pan){ //piirretään objekti, tätä ei koskaan kutsuta itse
	float x = (float) getVectVal(getObjAttr(object, 'p'), 0);
	float y = (float) getVectVal(getObjAttr(object, 'p'), 1);
	ALLEGRO_COLOR color = al_map_rgb(200,200,200);
	//float delta_x = 320;
	//float delta_y = 240;
	//if (pan != NULL){
	//multVect(pan,scale);
	float deltax = getVectVal(pan,0);
	float deltay = getVectVal(pan,1);

	//deltax = scaleVal(deltax,1/scale);
	//deltay = scaleVal(deltay,1/scale);
	//aluksi pitää määrittää sopivat arvot x:lle ja y:lle,
	//eli: x ja y pitää olla sellaisia, että x etäisyys 
	//ruudun keskikohdasta, samoin y. sitten voi skaalata
	
	
	x = panVal(x,deltax);//tehty?
	y = panVal(y,deltay);//tehty?
	x = scaleVal(x,scale);
	y = scaleVal(y,scale);
	

	
	
	
	//}
	al_draw_filled_circle(x+320,y+240,4,color);
}
void drawObjList(ObjList * list, double scale, Vect * pan){//piirretaan lista, tätä kutsutaan itse.
	for (size_t i=0;i<list->size;i++)
		drawObj(list->obj[i],scale, pan);
}
