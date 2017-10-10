#include <stdio.h>
#include <math.h>

#define PI 3.14159

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

double cosMaclaurinFront(double x, long int k){  //obliczanie ze wzoru od początku

  double sum = 0.0;

  for(long int i=0; i<=k; i++){
      sum += potega(-1, i) * potega(x, 2*i) / silnia(2*i);
  }
  return sum;
}

double cosMaclaurinBack(double x, long int k){  //ze wzoru od tyłu

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

double cosFront(double x, long int k){      //od przodu na podstawie poprzedniego

  double t   = 1.0;
  double sum = 1.0;

  for(long int i=1; i<=k; i++){
    t = t * (-1)*x*x / (2*i*(2*i-1));
    sum = sum + t;
  }

  return sum;
}

double cosBack(double x, long int k){       //co jest źle???

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

int main(){

  /*
  x       => szukany kąt w radianach
  k       => precyzja, ilość zer po przecinku
  result  => wynik operacji
  */

  double    x;
  long int  k;

  printf("\nPodaj szukany kąt: ");
  scanf("%lf", &x);
  printf("\nPodaj szukaną precyzję: ");
  scanf("%li", &k);

//  x = x * PI / 180; //zamiana na radiany

  printf("\nWynik wbudowanej funkcji: %.54lf\n", cos(x));

  printf("\nWynik zaimplementowanej fukncji od przodu: %.54lf\n", cosFront(x, k));

  printf("\nWynik zaimplementowanej fukncji od tyłu: %.54lf\n", cosBack(x, k));

  printf("\nWynik zaimplementowanej fukncji ze wzoru: %.54lf\n", cosMaclaurinFront(x, k));

  printf("\nWynik zaimplementowanej fukncji ze wzoru2: %.54lf\n", cosMaclaurinBack(x, k));

  return 0;
}
