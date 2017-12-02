///////////////////////
// Pairing functions //
// @illumitata       //
///////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4 // size of integer array

// Recursive Cantor Pairing Function
unsigned long int CantorPair(int* tab, int n) {

  unsigned long int result;

  // Original formula:
  // 0.5 * (x + y) * (x + y + 1) + y
  // Can be also represented as polynomial in such way:
  // (x^2 + 3x + 2xy + y + y^2) / 2
  // First one is better in recursion means
  // We need to call "inside pair" only two times
  if(n > 1) result = ((CantorPair(tab, n-1) + tab[n]) * \
                      (CantorPair(tab, n-1) + tab[n] + 1)) / 2 + tab[n];
  else result = ((tab[n-1] + tab[n]) * (tab[n-1] + tab[n] + 1)) / 2 + tab[n];

  return result;
}
// Reverse the reuslt of function into integers
int* CantorUnPair(int* tab, int number, int n) {

  int w = (int)(floor((sqrt(8 * number + 1) - 1) / 2));
  int t = ((int)(pow(w, 2.0)) + w) / 2;
  int y = number - t;
  int x = w - y;

  if(n > 1) {
    tab[n] = y;
    CantorUnPair(tab, x, n-1);
  }
  else{
    tab[n] = y;
    tab[n-1] = x;
  }
  return tab;
}

// Method from: szudzik.com/ElegantPairing.pdf
// Helping method finding maximum from two numbers
int max(int a, int b){
  if(a > b) return a;
  else return b;
}

unsigned long int ElegantPair(int* tab, int n) {

  unsigned long int result;

  if(n > 1) {
    if(ElegantPair(tab, n-1) != max(ElegantPair(tab, n-1), tab[n]))
      result = tab[n] * tab[n] + ElegantPair(tab, n-1);
    else result = ElegantPair(tab, n-1) * ElegantPair(tab, n-1) \
                  + ElegantPair(tab, n-1) + tab[n];
  }
  else {
    if(tab[n-1] != max(tab[n-1], tab[n])) result = tab[n] * tab[n] + tab[n-1];
    else result = tab[n-1] * tab[n-1] + tab[n-1] + tab[n];
  }
  return result;
}

int* ElegantUnPair(int* tab, int number, int n) {

  int numberFloor = (int)(floor(sqrt(number)));

  int comparisonTmp = number - (int)(pow(numberFloor, 2.0));

  if(n > 1) {
    if(comparisonTmp < numberFloor) {
      tab[n] = numberFloor;
      int numberTmp = number - (int)(pow(numberFloor, 2.0));
      ElegantUnPair(tab, numberTmp, n-1);
    }
    else {
      tab[n] = number - (int)(pow(numberFloor, 2.0)) - numberFloor;
      ElegantUnPair(tab, numberFloor, n-1);
    }
  }
  else {
    if(comparisonTmp < numberFloor) {
      tab[n] = numberFloor;
      tab[n-1] = number - (int)(pow(numberFloor, 2.0));
    }
    else {
      tab[n] = number - (int)(pow(numberFloor, 2.0)) - numberFloor;
      tab[n-1] = numberFloor;
    }
  }

  return tab;
}

int main() {

  int tab[N] = {1, 1, 3, 5};

  unsigned long int reusultCantor = CantorPair(tab, N-1);
  printf("CantorPair:%10li\n", reusultCantor);

  printf("CantorUnPair:");
  // Array storing unpair integers
  //int *tabCantor = calloc(N, sizeof(int));
  int *tabCantor = malloc(sizeof *tab);
  tabCantor = CantorUnPair(tabCantor, reusultCantor, N-1);
  for(int i = 0; i < N; i++) printf("%5i", tabCantor[i]);
  free(tabCantor);

  printf("\n");

  unsigned long int resultElegant = ElegantPair(tab, N-1);
  printf("ElegantPair:%10li\n", resultElegant);

  printf("ElegantUnPair:");
  // int *tabElegant = calloc(N, sizeof(int));
  int *tabElegant = malloc(sizeof *tab);
  tabElegant = ElegantUnPair(tabElegant, resultElegant, N-1);
  for(int i = 0; i < N; i++) printf("%5i", tabElegant[i]);
  free(tabElegant);

  printf("\n");

  return 0;
}
