#ifndef OBJLIST
#define OBJLIST

#include "movement.h"

//tämä headeri sisältää ObjList-rakenteen, jota käytetään objektien yhteen
// sitomiseen ja niiden käsittelyn helpottamiseen. Lista on 1-ulotteinen,
//ja käytetään nyt aluksi ihan dynaamista taulukkoa, linkitetty lista tulee
//myöhemmin jos tulee.

typedef struct ObjList{
	size_t size;
	Obj ** obj;
}ObjList;

ObjList * createObjList();

void addObj(ObjList * objlist, Obj * obj);

void removeObj(ObjList * objlist, size_t index);

void destroyObjList(ObjList * objlist);

void updateAcc(ObjList * objlist,int forcetoggle);//päivittää kaikkien objektien kiihtyvyydet

void updateVel(ObjList * objlist);//päivittää objektien nopeudet

void updatePos(ObjList * objlist);//päivittää kaikkien objektien paikat


#endif
