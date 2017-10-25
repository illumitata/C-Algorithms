#include <stdio.h>
#include <math.h>

#include "cosinus.h"

unsigned long int silnia(long int n){
  if (n == 0) return 1;
  else return n*silnia(n-1);
}

long double potega(long double x, long int n){

  long double wynik = 1.0;

  for(long int i=1; i<=n; i++){
      wynik*=x;
  }
  return wynik;
}

//obliczanie z rozwinięcia Maclaurina od przodu
long double cosMaclaurinFront(long double x, long int k){

  long double sum = 0.0;

  for(long int i=0; i<=k; i++){
      sum += potega(-1, i) * potega(x, 2*i) / silnia(2*i);
  }

  return sum;
}

//obliczanie z rozwinięcia Maclaurina od tyłu
long double cosMaclaurinBack(long double x, long int k){

  long double sum = 0.0;
  long double tmp[k];

  for(long int i=0; i<=k; i++){
      tmp[i] = potega(-1, i) * potega(x, 2.0*i) / silnia(2.0*i);
  }

  for(long int i=k; i>=0; i--){
      sum += tmp[i];
  }

  return sum;
}

//obliczanie na podstawie poprzedniego wyrazu od przodu
long double cosFront(long double x, long int k){

  long double t   = 1.0;
  long double sum = 1.0;

  for(long int i=1; i<=k; i++){
    t = t * (-1)*x*x / (2.0*i*(2.0*i-1.0));
    sum = sum + t;
  }

  return sum;
}

//obliczanie na podstawie poprzedniego wyrazu od tyłu
long double cosBack(long double x, long int k){

  long double sum = 0.0;
  long double tmp[k+1];

  tmp[0] = 1.0;

  for(long int i=1; i<=k; i++){
    tmp[i] = tmp[i-1] * (-1)*x*x / (2.0*i*(2.0*i-1.0));
  }

  for(long int i=k; i>=0; i--){
    sum += tmp[i];
  }

  return sum;
}
