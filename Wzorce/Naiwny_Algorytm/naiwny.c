//implementacja algorytmu naiwnego wyszukiwania wzorca w tekście

#include <stdio.h>
#include <stdlib.h>
#include "tablica.h"
#include <time.h>

#define DL   300000

void Naiwny(char* P, char* T, int n, int m){
// P - wzorzec, tablica [1..m],
// T - tekst, tablica [1..n],
  int s = 0;
  int k = 0;
  char wynik[m];

    for(s=0; s < (n-m); s++){
      for(k=0; k<m; k++){
        if(P[k]==T[s+k]){
          wynik[k]=T[s+k];
        }                                                   //tu porównujemy m znaków (w pętli)
      }

      for(k=0; k<m; k++){
        if(wynik[k]!=P[k]) break;
        if(k==m-1){
          //for(k=0; k<m; k++) printf("%c", wynik[k]);      //dla mniejszych wzorców, wzorzec przykładowy psuje czytelność
          printf(" || Znaleziono na pozycji %d\n", s+1);    //Mogę pokazać w atomie AAAA|CBCAAA, gdzie kreska to pozycja
        }
      }
      for(k=0; k<m; k++) wynik[k] = 0;                     //czyszczenie pętli wynikowej
    }

  return;
}

int main(){

  char nazwa_tekstu[100];
  char nazwa_wzorca[100];

  system("clear");

  printf("Program korzystający z algorytmu naiwnego.\n\n");

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

  Naiwny(wzorzec, tekst, n, m);

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
