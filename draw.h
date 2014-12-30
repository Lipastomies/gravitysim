#ifndef DRAW
#define DRAW

#include "objlist.h" //fysiikat ja objektien kanssa leikkiminen
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

void drawObj(Obj * object , double scale); //piirretään objekti, tätä
										   // ei koskaan kutsuta itse

void drawObjList(ObjList * list, double scale);//piirretaan lista,
											   //tätä kutsutaan itse.


#endif
