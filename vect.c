
#include "vect.h"

/*typedef struct Vect {
	double x,y;
}Vect;*/

Vect * createVect(){
	Vect * vector = malloc(sizeof(Vect));
	setVect(vector,0,0);
	return vector;
}
void setVect(Vect * vector, double x, double y){
	vector->x = x;
	vector->y = y;
}
Vect * getVect(Vect * vector){
	return vector;
}

double getVectVal(Vect * vector, size_t choice){
	if (choice == 0)
		return vector->x;
	if (choice == 1)
		return vector->y;
	else return 0;
}

void destroyVect(Vect * vector){
	free(vector);
}

void addVect(Vect * A, Vect * B){ //lisää A:han B:n
	//Vect * retval = createVect();
	setVect(A, getVectVal(A,0)+getVectVal(B,0),getVectVal(A,1)+getVectVal(B,1));
}

void substractVect(Vect * A, Vect * B){ //vähentää A:sta B:n
	//Vect * retval = createVect();
	setVect(A, getVectVal(A,0)-getVectVal(B,0),getVectVal(A,1)-getVectVal(B,1));;
}

void multVect(Vect * A, double scalar){
	setVect(A, getVectVal(A,0)*scalar, getVectVal(A,1)*scalar);
}

void printVect(Vect * vector){
	printf("vector : (%lf, %lf)\n",vector->x,vector->y);
}

double calcDist(Vect * A, Vect * B){
	double deltax = getVectVal(A,0)-getVectVal(B,0);
	double deltay = getVectVal(A,1)-getVectVal(B,1);
	return sqrt(deltax*deltax+ deltay*deltay);
}


