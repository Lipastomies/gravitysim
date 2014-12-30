#include "obj.h"

/*
typedef struct Vect {
	double x,y;
}Vect;


typedef struct Obj {
	double mass;
	Vect * pos,vel,acc;
}Obj;*/

Obj * createObj(double mass){
	Obj * obj = malloc(sizeof(Obj));
	obj->pos = createVect();
	//SetVect(obj->pos,0,0);
	obj->vel = createVect();
	//SetVect(obj->vel,0,0);
	obj->acc = createVect();
	obj->mass = mass;
	return obj;
}

Obj * copyObj(Obj * object){//luo uuden objektin, joka täytyy erikseen tuhota
	Obj * newobj = createObj( getObjMass(object));
	setObjAttr (newobj, getObjAttr(object,'p'),'p'); 
	setObjAttr (newobj, getObjAttr(object,'v'),'v'); 
	setObjAttr (newobj, getObjAttr(object,'a'),'a'); 
	return newobj;
}

void setObjVal(Obj * obj, double x, double y, char attribute){
	switch (attribute){
		case 'a': setVect(obj->acc, x, y);
		break;
		case 'p': setVect(obj->pos, x, y);
		break;
		case 'v': setVect(obj->vel, x, y);
		break;
		default:
		fprintf(stderr, "INVALID ATTRIBUTE CODE IN FUNCTION setObjAtrr()\n");
		break;
	}
}

void setObjAttr(Obj * obj, Vect * vector, char attribute){
	switch (attribute){
		case 'a': setVect(obj->acc, getVectVal(vector,0),getVectVal(vector,1));
		break;
		case 'p': setVect(obj->pos, getVectVal(vector,0),getVectVal(vector,1));
		break;
		case 'v': setVect(obj->vel, getVectVal(vector,0),getVectVal(vector,1));
		break;
		default:
		fprintf(stderr, "INVALID ATTRIBUTE CODE IN FUNCTION setObjAtrr()\n");
		break;
	}
}

Vect * getObjAttr(Obj * obj, char attribute){
	switch (attribute){
		case 'a':return getVect(obj->acc);
		break;
		case 'p':return getVect(obj->pos);
		break;
		case 'v':return getVect(obj->vel);
		break;
		default:
		fprintf(stderr, "INVALID ATTRIBUTE CODE IN FUNCTION getObjAttr()\n");
		return NULL;
		break;
	}
}

double getObjMass(Obj * obj){
	return obj->mass;
}

void setObjMass(Obj * obj, double mass){
	obj->mass = mass;
}


void destroyObj(Obj* obj){
	destroyVect(obj->pos);
	destroyVect(obj->vel);
	destroyVect(obj->acc);
	free(obj);
}

void printObj(Obj* obj){
	//Objektin paikka, nopeus, massa
	printf("Object mass: %lf\n",obj->mass);
	printf("Object position ");
	printVect(obj->pos);
	printf("Object velocity ");
	printVect(obj->vel);
}

void printPos(Obj * obj){//muokatttu octavelle sopivaksi, eli x y;
	printf("%.2lf %.2lf",getVectVal(getObjAttr(obj,'p'),0),getVectVal(getObjAttr(obj,'p'),1));
}
