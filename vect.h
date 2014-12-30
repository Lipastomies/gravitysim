#ifndef VECT
#define VECT
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

typedef struct Vect {
	double x,y;
}Vect;

Vect * createVect();
void setVect(Vect * vector, double x, double y);
Vect * getVect(Vect * vector);
double getVectVal(Vect * vector, size_t choice);
void destroyVect(Vect * vector);
void addVect(Vect * A, Vect * B);//lisää A:han B:n
void substractVect(Vect * A, Vect * B);
void multVect(Vect * A, double scalar);
void printVect(Vect * vector); //debug
double calcDist(Vect * A, Vect * B); //etäisyys
#endif
