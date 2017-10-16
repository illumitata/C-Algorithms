#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "cosinus.h"

#define DATA_ITER   0.01    //ilość o jaką zwiększa się kąt
//#define DATA_MAX    6.28    //(6.28 rad = 360 stopni)
#define POWER_ITER  1       //o ile zwiększamy "potęgę", czyli dokładność
#define POWER_MAX   200     //maksymalna dokładność

int main(){

  //dla każdej zaimplementowanej funkcji
  //wykonaj dla 0<x<6.28 => |cos(x) - cosWłasny(x, n)|
  //każdy z wyników, wypisz do pliku o nazwie danej funkcji w formie:
  //(pusta linia)
  //(///////////)
  //(wartość x : błąd)
  //(wartość x : błąd)
  //...
  //(wartość x : błąd)
  //!EOF
  //
  //(czy tak ważne) pobierz ponownie dane z pliku do tablicy, posortuj je szybko
  //dodawaj od najmniejszej do największej
  //średnia arytmetyczna z tego i wypisanie jej do pierwszej linii pliku
  //w formie:
  //(wartość średniej)
  //(////////////)
  //...reszta pliku
  //wypisz z każdego pliku średnie błędy
  //porównaj je i wyciągnij wnioski

  //IN FUTURE: porównaj pamięci obliczeniowe dla każdej metody

////////////////////////////////////////////////
  FILE *a = fopen("wynik1.txt", "w");

  if (a == NULL){
    printf("Error opening file!\n");
    exit(1);
  }


  double funcError = 0.0;

  for(long int n=1; n<=POWER_MAX; n+=POWER_ITER){
    for(double i=(-1)*M_PI; i<=M_PI; i+=DATA_ITER){
      funcError = cos(i) - cosMaclaurinFront(i, n);
      funcError = fabsl(funcError);
      if(funcError>2) fprintf(a, "%ld ||| %lf ||| ???\n", n, i);
      else fprintf(a, "%ld ||| %lf ||| %.16lf\n", n, i, funcError);
    }
  }

  fclose(a);

////////////////////////////////////////////////
  FILE *b = fopen("wynik2.txt", "w");

  if (b == NULL){
    printf("Error opening file!\n");
    exit(1);
  }


  funcError = 0.0;

  for(long int n=1; n<=POWER_MAX; n+=POWER_ITER){
    for(double i=(-1)*M_PI; i<=M_PI; i+=DATA_ITER){
      funcError = cos(i) - cosMaclaurinBack(i, n);
      funcError = fabsl(funcError);
      if(funcError>2) fprintf(b, "%ld ||| %lf ||| ???\n", n, i);
      else fprintf(b, "%ld ||| %lf ||| %.16lf\n", n, i, funcError);
    }
  }

  fclose(b);

////////////////////////////////////////////////
  FILE *c = fopen("wynik3.txt", "w");

  if (c == NULL){
    printf("Error opening file!\n");
    exit(1);
  }


  funcError = 0.0;

  for(long int n=1; n<=POWER_MAX; n+=POWER_ITER){
    for(double i=(-1)*M_PI; i<=M_PI; i+=DATA_ITER){
      funcError = cos(i) - cosFront(i, n);
      funcError = fabsl(funcError);
      if(funcError>2) fprintf(c, "%ld ||| %lf ||| ???\n", n, i);
      else fprintf(c, "%ld ||| %lf ||| %.16lf\n", n, i, funcError);
    }
  }

  fclose(c);

////////////////////////////////////////////////
  FILE *d = fopen("wynik4.txt", "w");

  if (d == NULL){
    printf("Error opening file!\n");
    exit(1);
  }


  funcError = 0.0;

  for(long int n=1; n<=POWER_MAX; n+=POWER_ITER){
    for(double i=(-1)*M_PI; i<=M_PI; i+=DATA_ITER){
      funcError = cos(i) - cosBack(i, n);
      funcError = fabsl(funcError);
      if(funcError>2) fprintf(d, "%ld ||| %lf ||| ???\n", n, i);
      else fprintf(d, "%ld ||| %lf ||| %.16lf\n", n, i, funcError);
    }
  }

  fclose(d);

  return 0;
}
