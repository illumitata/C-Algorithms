#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "cosinus.h"

#define DATA_ITER   0.001   //ilość o jaką zwiększa się kąt
#define POWER_ITER  1       //o ile zwiększamy "potęgę", czyli dokładność
#define POWER_MAX   40      //maksymalny krok

int main(){

  /*
  Dla każdej funkcji średnia arytmetyczna ze wszystkich błędów dla kroku
    krok, radian, error
  */

  //IN FUTURE: porównaj pamięci obliczeniowe dla każdej metody

////////////////////////////////////////////////
  FILE *a = fopen("macfrontdiff.csv", "w+");

  if (a == NULL){
    printf("Error opening file!\n");
    exit(1);
  }

  long double funcError = 0.0;

  fprintf(a, "krok,radian,error\n");

  for(long int n=1; n<=POWER_MAX; n+=POWER_ITER){
    for(long double i=(-1)*M_PI; i<=M_PI; i+=DATA_ITER){
      funcError = cosl(i) - cosMaclaurinFront(i, n);
      funcError = fabsl(funcError);
      //if(funcError>2) fprintf(a, "%ld ||| %Lf ||| ???\n", n, i);
      //else
      fprintf(a, "%ld,%Lf,%.20Lf\n", n, i, funcError);
    }
  }

  fclose(a);

////////////////////////////////////////////////
  FILE *b = fopen("macbackdiff.csv", "w+");

  if (b == NULL){
    printf("Error opening file!\n");
    exit(1);
  }

  funcError = 0.0;

  fprintf(b, "krok,radian,error\n");

  for(long int n=1; n<=POWER_MAX; n+=POWER_ITER){
    for(long double i=(-1)*M_PI; i<=M_PI; i+=DATA_ITER){
      funcError = cosl(i) - cosMaclaurinBack(i, n);
      funcError = fabsl(funcError);
      //if(funcError>2) fprintf(b, "%ld ||| %Lf ||| ???\n", n, i);
      //else
      fprintf(b, "%ld,%Lf,%.20Lf\n", n, i, funcError);
    }
  }

  fclose(b);

////////////////////////////////////////////////
  FILE *c = fopen("nextfrontdiff.csv", "w+");

  if (c == NULL){
    printf("Error opening file!\n");
    exit(1);
  }

  funcError = 0.0;

  fprintf(c, "krok,radian,error\n");

  for(long int n=1; n<=POWER_MAX; n+=POWER_ITER){
    for(long double i=(-1)*M_PI; i<=M_PI; i+=DATA_ITER){
      funcError = cosl(i) - cosFront(i, n);
      funcError = fabsl(funcError);
      //if(funcError>2) fprintf(c, "%ld ||| %Lf ||| ???\n", n, i);
      //else
      fprintf(c, "%ld,%Lf,%.20Lf\n", n, i, funcError);
    }
  }

  fclose(c);

////////////////////////////////////////////////
  FILE *d = fopen("nextbackdiff.csv", "w+");

  if (d == NULL){
    printf("Error opening file!\n");
    exit(1);
  }

  funcError = 0.0;

  fprintf(d, "krok,radian,error\n");

  for(long int n=1; n<=POWER_MAX; n+=POWER_ITER){
    for(long double i=(-1)*M_PI; i<=M_PI; i+=DATA_ITER){
      funcError = cosl(i) - cosBack(i, n);
      funcError = fabsl(funcError);
      //if(funcError>2) fprintf(d, "%ld ||| %Lf ||| ???\n", n, i);
      //else
      fprintf(d, "%ld,%Lf,%.20Lf\n", n, i, funcError);
    }
  }

  fclose(d);

  return 0;
}
