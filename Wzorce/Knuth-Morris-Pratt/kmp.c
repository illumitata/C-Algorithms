//implementacja algorytmu Knutha-Morrisa-Pratta wyszukiwania wzorca w tekście
//(Naprawione)z dziwnych przyczyn dla wzora w stylu "bbb" wypisuje jeszcze prefiks "bb" jako wzorzec
//Nie czyta ostatniego wzorca jak nie ma po nim litery???

#include <stdio.h>
#include <stdlib.h>
#include "tablica.h"
#include <time.h>

#define DL   300000

int* PrefixFunction(char* P, int m, int n){
// P - wzorzec, tablica [1..m]
  int* pi = (int*) malloc(sizeof(*pi) * n);
  int k = 0;
  int q = 0;

    pi[0] = 0;                //może być 0 (nawet musi)

    for(q=2; q<m+1; q++){     //nie wiem czy nie wstawić tu m+1, doświadczenie z automatu skończonego
      while(k>0 && (P[k]!=P[q-1])){
        k = pi[k-1];
      }
      if(P[k]==P[q-1]){
        k = k+1;
      }
      pi[q-1]=k;
    }

return pi;
}

void KMP(char* P, char* T, int n, int m){
// T - tekst, tablica [1..n]
// P - wzorzec, tablica [1..m]

  int i = 0;

    int* pitab = PrefixFunction(P, m, n);

    //for(i=0; i<10; i++) printf("%d\n", pitab[i]);
    int a = 0;

    for(i=0; i<n; i++){
      while(a>0 && (P[a]!=T[i-1])){
        a = pitab[a-1];
      }
      if(P[a]==T[i-1]){
        a = a+1;
      }
      if(a==m){
        printf("|| Znaleziono na pozycji: %d\n", i-m+1);
        a = pitab[a];
      }
    }

  free(pitab);

  return;
}

int main(){

  char nazwa_tekstu[100];
  char nazwa_wzorca[100];

  system("clear");

  printf("Program korzystający z algorytmu Knutha-Morrisa-Pratta.\n\n");

  printf("Podaj nazwę pliku TEKSTU do wczytania: ");
  scanf ("%s", nazwa_tekstu);                                         //wczytywany tekst

    char* tekst = przepisz(nazwa_tekstu, DL);
    int n = ileznakow();
    printf("Długość: %d\n", n);

  printf("\n\nPodaj nazwę pliku WZORCA do wczytania: ");
  scanf ("%s", nazwa_wzorca);                                         //wczytywany wzorzec

    char* wzorzec = przepisz(nazwa_wzorca, DL);
    int m = ileznakow();
    printf("Długość: %d\n\n", m);

  printf("Start algorytmu...\n");
  time_t czasStart = time( NULL );
  clock_t zegarStart = clock();

  KMP(wzorzec, tekst, n, m);

  clock_t zegarStop = clock();
  time_t czasStop = time( NULL );
  printf("Koniec algorytmu.\n\n");
  printf("Czas jego trwania : %.2f sekund.\n", difftime(czasStop,czasStart));
  printf("Czas przetwarzania: %.2f\n", (double) zegarStop - zegarStart);

  printf("\n\n");

  free(tekst);
  free(wzorzec);

  return 0;
}
