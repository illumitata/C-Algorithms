///////////////////////
// Pairing functions //
// @illumitata       //
///////////////////////
#include <stdio.h>
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

// Method from: szudzik.com/ElegantPairing.pdf
// Helping method max (TO DO: think about max from same numbers)
int max(int a, int b){
  if(a > b) return a;
  else return b;
}

unsigned long int ElegantPair(int* tab, int n) {

  unsigned long int result;

  if(n > 1) {
    if(tab[n-1] != max(tab[n-1], tab[n])) result = tab[n] * tab[n] \
                                                   + ElegantPair(tab, n-1);
    else result = ElegantPair(tab, n-1) * ElegantPair(tab, n-1) \
                  + ElegantPair(tab, n-1) + tab[n];
  }
  else {
    if(tab[n-1] != max(tab[n-1], tab[n])) result = tab[n] * tab[n] + tab[n-1];
    else result = tab[n-1] * tab[n-1] + tab[n-1] + tab[n];
  }
  return result;
}

int main() {

  int tab[N] = {2, 4, 6, 3};

  unsigned long int reusultCantor = CantorPair(tab, N-1);
  printf("CantorPair: %10li\n", reusultCantor);

  unsigned long int resultElegant = ElegantPair(tab, N-1);
  printf("ElegantPair:%10li\n", resultElegant);

  return 0;
}
