#ifndef MOVEMENT
#define MOVEMENT
#include "obj.h"

void moveObj(Obj * object);
//laske voima
//muuta nopeusvektoria
void accelerateObj(Obj * object);
double absForce(Obj * A, Obj * B);
Vect * calcAcc(Obj * A, Obj * B); //käytetään siten, että tämä luo vect-tyypin, joka pitää itse vapauttaa.

#endif
