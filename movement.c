#include "movement.h"

void moveObj(Obj * object){//tällä päivitetään paikka
	//double a = 1;//hattuvakio
	addVect(getObjAttr(object,'p'),getObjAttr(object,'v'));
	//setObjVal(object,a*getVectVal(newpos,0),a*getVectVal(newpos,1),'p');
	//setObjPos(object, a*getVectVal(getObjVel(object),0),a*getVectVal(getObjVel(object),1));
}
void accelerateObj(Obj * object){//tällä päivitetään nopeus 
	//double a = 1;//hattuvakio
	addVect(getObjAttr(object,'v'),getObjAttr(object,'a'));
	//setObjVal(object,getVectVal(newvel,0),getVectVal(newvel,1),'v');
	//destroyVect(newvel);
	//setObjVal(object,getVectVal(getObjAttr(A,'a'),0),getVectVal(getObjAttr(A,'a'),0),'v');
}
double absForceSquare(Obj * A, Obj * B){ //palauttaa voiman skalaari-
								   //arvon, ei siis laske vektoria.
	double dist = calcDist(getObjAttr(A, 'p'), getObjAttr(B, 'p'));
	//printf("%lf\n", dist);
	if (dist != 0)
		return (getObjMass(A)*getObjMass(B))/(dist*dist);
	return 0;
}

//muita voimia, joita voi valita : 1/r

double absForceLinear(Obj * A, Obj * B){ //palauttaa voiman skalaari-
								   //arvon, ei siis laske vektoria.
	double dist = calcDist(getObjAttr(A, 'p'), getObjAttr(B, 'p'));
	//printf("%lf\n", dist);
	if (dist != 0)
		return (getObjMass(A)*getObjMass(B))/(dist);
	return 0;
}

Vect * calcAcc(Obj * A, Obj * B){//A on vaikutettava objekti, B on vaikuttava
	Vect * Temp = createVect();
	double absforce = absForceSquare(A, B);
	double deltax = getVectVal(getObjAttr(B,'p'),0)-getVectVal(getObjAttr(A,'p'),0);
	double deltay = getVectVal(getObjAttr(B,'p'),1)-getVectVal(getObjAttr(A,'p'),1);
	double xforce = (deltax)/(calcDist(getObjAttr(B,'p'), getObjAttr(A,'p')))*absforce/getObjMass(A);
	//printf("%lf , %lf \n",deltax, calcDist(getObjAttr(B,'p'), getObjAttr(A,'p')));
	double yforce = (deltay)/(calcDist(getObjAttr(B,'p'), getObjAttr(A,'p')))*absforce/getObjMass(A);
	//printf("%lf , %lf \n",deltay, calcDist(getObjAttr(B,'p'), getObjAttr(A,'p')));
	setVect(Temp, xforce,yforce);
	//printVect(Temp);
	return Temp;
}
