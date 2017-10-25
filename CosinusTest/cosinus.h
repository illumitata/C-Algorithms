#ifndef COSINUS_H
#define COSINUS_H

#include <stdio.h>
#include <math.h>

#include "cosinus.h"

long double cosMaclaurinFront(long double x, long int k);

long double cosMaclaurinBack(long double x, long int k);

long double cosFront(long double x, long int k);

long double cosBack(long double x, long int k);

#endif
