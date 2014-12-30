#ifndef OBJ
#define OBJ

#include "vect.h"


typedef struct Obj {
	double mass;
	Vect * pos;
	Vect * vel;
	Vect * acc;
	//double vel_x, vel_y;
}Obj;

Obj * createObj(double mass);
Obj * copyObj(Obj * object);
void setObjVal(Obj * obj, double x, double y, char attribute);

void setObjAttr(Obj * obj, Vect * vector, char attribute);
Vect * getObjAttr(Obj * obj, char attribute);
void setObjPos(Obj * obj,double x, double y);//deprecated
double getObjMass(Obj * obj);
void setObjMass(Obj * obj, double mass);
void destroyObj(Obj* obj);
void printObj(Obj* obj);
void printPos(Obj * obj);//plot in wolframaplha
#endif
