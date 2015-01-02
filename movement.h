#ifndef MOVEMENT
#define MOVEMENT
#include "obj.h"

void moveObj(Obj * object);
//laske voima
//muuta nopeusvektoria
void accelerateObj(Obj * object);
double absForceSquare(Obj * A, Obj * B);
double absForceLinear(Obj * A, Obj * B);
double absForceSquareSoft(Obj * A, Obj * B);
Vect * calcAcc(Obj * A, Obj * B, int forcetoggle); //käytetään siten, että tämä luo vect-tyypin, joka pitää itse vapauttaa.

#endif
