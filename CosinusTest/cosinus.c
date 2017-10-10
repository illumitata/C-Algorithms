#include <stdio.h>
#include <math.h>

#include "cosinus.h"

long int silnia(long int n){
  if (n == 0) return 1;
  else return n*silnia(n-1);
}

double potega(double x, long int n){

  double wynik = 1.0;

  for(long int i=1; i<=n; i++){
      wynik*=x;
  }
  return wynik;
}

//obliczanie z rozwinięcia Maclaurina od przodu
double cosMaclaurinFront(double x, long int k){

  double sum = 0.0;

  for(long int i=0; i<=k; i++){
      sum += potega(-1, i) * potega(x, 2*i) / silnia(2*i);
  }
  return sum;
}

//obliczanie z rozwinięcia Maclaurina od tyłu
double cosMaclaurinBack(double x, long int k){

  double sum = 0.0;
  double tmp[k];


  for(long int i=0; i<=k; i++){
      tmp[i] = potega(-1, i) * potega(x, 2*i) / silnia(2*i);
  }

  for(long int i=k-1; i>=0; i--){
      sum += tmp[i];
  }

  return sum;
}

//obliczanie na podstawie poprzedniego wyrazu od przodu
double cosFront(double x, long int k){

  double t   = 1.0;
  double sum = 1.0;

  for(long int i=1; i<=k; i++){
    t = t * (-1)*x*x / (2*i*(2*i-1));
    sum = sum + t;
  }

  return sum;
}

//obliczanie na podstawie poprzedniego wyrazu od tyłu
double cosBack(double x, long int k){

  double sum = 0.0;
  double tmp[k+1];

  tmp[0] = 1.0;

  for(long int i=1; i<=k; i++){
    tmp[i] = tmp[i-1] * (-1)*x*x / (2*i*(2*i-1));
  }

  for(long int i=k; i>=0; i--){
    sum += tmp[i];
  }

  return sum;
}
