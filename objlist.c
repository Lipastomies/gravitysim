

#include "objlist.h"

//tämä headeri sisältää ObjList-rakenteen, jota käytetään objektien yhteen
// sitomiseen ja niiden käsittelyn helpottamiseen. Lista on 1-ulotteinen,
//ja käytetään nyt aluksi ihan dynaamista taulukkoa, linkitetty lista tulee
//myöhemmin jos tulee.

/*typedef struct ObjList{
	size_t size;
	Obj ** obj;
}ObjList;*/

ObjList * createObjList(){
	ObjList * objlist = malloc(sizeof(ObjList));
	objlist->size = 0;
	objlist->obj = malloc(sizeof(Obj*)*objlist->size);
	return objlist;
}

void addObj(ObjList * objlist, Obj * obj){
	objlist->size +=1;
	objlist->obj = realloc( objlist->obj,sizeof(Obj *)*objlist->size);
	objlist->obj[objlist->size-1] = obj;
}

void removeObj(ObjList * objlist, size_t index){
	if (index < objlist->size){ //tähän muuten pitää siirtää niitä kaikkia vitun objekteja... -,-'
		//luo uusi pointteri objlist->obj-taulukkoon, jotta tämä voidaan poistaa, kun uusi taulukko on siirretty objlist->obj-taulukoksi
		Obj ** newpointer = objlist->obj;
		Obj ** newobj = malloc((objlist->size-1)*sizeof(Obj * ));
		size_t laskuri = 0;
		for (size_t i = 0; i<objlist->size;i++){
			if (i != laskuri){
				newobj[laskuri] = copyObj(objlist->obj[i]);
				laskuri++;
			}
		}
		//asetetaan objlist->obj olemaan newobj, eli nyt itse operaatio tehty,
		//jäljellä enää siivousta
		objlist->obj = newobj;
		//tuhotaan sekä newpointerin objektit että newpointer (entinen objlist->obj)
		for (size_t i = 0;i<objlist->size;i++){
			destroyObj(newpointer[i]);
		}
		objlist->size -=1;
		free(newpointer);
	}
}

void destroyObjList(ObjList * objlist){
	for (size_t i = 0; i < objlist->size;i++)
		destroyObj(objlist->obj[i]);
	free (objlist->obj);
	free(objlist); 
}

void updateAcc(ObjList * objlist, int forcetoggle){//päivittää kaikkien objektien kiihtyvyydet
	for (size_t i=0;i<objlist->size;i++){//käy läpi kaikki objektit
		//nollataan nykyinen kiihtyvyys
		setVect(getObjAttr(objlist->obj[i],'a'),0,0);
		Vect * sum = createVect();//summakiihtyvyys
		for (size_t j=0;j<objlist->size;j++){
			if (j!=i){
				Vect * acc = calcAcc( objlist->obj[i],objlist->obj[j],forcetoggle);
				addVect(sum,acc);
				destroyVect(acc);
			}
		}
		//sijoita kiihtyvyys objektiin
		setObjAttr(objlist->obj[i],sum,'a');
		destroyVect(sum);
		//printVect(sum);//debug, printtaa kiihtyvyyden arvot.
	}
}

void updateVel(ObjList * objlist){//päivittää objektien nopeudet
	for (size_t i=0;i<objlist->size;i++){//käy läpi kaikki objektit
		accelerateObj(objlist->obj[i]);
	}
}

void updatePos(ObjList * objlist){//päivittää kaikkien objektien paikat
	for (size_t i=0;i<objlist->size;i++){//käy läpi kaikki objektit
		moveObj(objlist->obj[i]);
	}
}
