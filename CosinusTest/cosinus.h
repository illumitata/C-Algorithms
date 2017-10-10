#ifndef COSINUS_H
#define COSINUS_H

#include <stdio.h>
#include <math.h>

#include "cosinus.h"

double cosMaclaurinFront(double x, long int k);

double cosMaclaurinBack(double x, long int k);

double cosFront(double x, long int k);

double cosBack(double x, long int k);

#endif
