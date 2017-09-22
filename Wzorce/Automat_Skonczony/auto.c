//implementacja algorytmu Automatu Skończonego przy wyszukiwaniu wzorca w tekście
//(Rozwiązane?)(***)Dodatkowo problem tworzy się przy "wew" --> "weeew" też czyta jak wzorzec
//Dlaczego? Automat w takim wypadku nie wraca do stanu zerowego, trzeba to poprawić ^^^
//Wszystko kwestią alokacji?

#include <stdio.h>
#include <stdlib.h>
#include "tablica.h"
#include <time.h>

#define DL        300000
static int alfabet = 128;       //zakładam 128 literowy alfabet ASCII

/////WSTAWKA Z Knutha-Morrisa-Pratta!
int* PrefixFunction(char* P, int m, int n){
// P - wzorzec, tablica [1..m]
  int* pi = (int*) malloc(sizeof(*pi) * m-1);
  int k = 0;
  int q = 0;

    pi[0] = 0;              //może być 0

    for(q=2; q<m+1; q++){   //po wyświetleniu tablicy brak m+1 powodował znikanie ostatniej f. pref.
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
/////KONIEC WSTAWKI

int** TransitionFunction(char* P, int m, int alfa, int n){
// P - wzorzec, tablica [1..m]
// S - alfabet znaków

  int z = 0;                                //nie wiem nakombinowane już
                                            //(**)dla samych n działa w obu wypadkach ale wolno
  int** d;                                  //(**)o dziwo DL u góry i n na dole i alfa niżej działa sprawniej
  d = malloc(sizeof(*d) * n);               //(**)dlaczego wszędzie DL żeby otworzyć plik duży. (dla małych alfa wystarczy)
  for(z = 0; z<n; z++){
    d[z] = malloc(sizeof(*d[z]) * alfa);    //(**)int zmieniłem na char, troszkę przyspieszyło
  }

  int* pitab2 = PrefixFunction(P, m, n);

  int q = 0;
  int a = 0;
  int l = 0;

  for(q=0; q<m; q++){
    for(a=0; a<alfa; a++){
      if(q==m || a!=(int)P[q]){           //redukcja do samego q zamiast q+1 pomaga na problem (PROBLEM)
        l = pitab2[q];
        d[q][a] = d[l][a];
      }
      else d[q][a] = q+1;
    }
  }

/*//POKAZUJE 128 wierszowy zapis automatu
printf("ELOCHA\n");
for(int p=0; p<alfa; p++){
  for(int u=0; u<m; u++) printf("%d ", d[u][p]);
  printf("\n");
}
  printf("\n\n\n");*/

  free(pitab2);
  return d;
}

void Automat(char* P, char* T, int n, int m){

  //char alfabetTab[alfabet] = {'a', 'b'};
  //char* alfabetTab = przepisz("alfabet.txt", alfabet);
  /*char* alfabetTab = (char*) malloc(sizeof(char*) * alfabet);
  for(int i=0; i<alfabet; i++) alfabetTab[i] = i;*/

  int** dd = TransitionFunction(P, m, alfabet, n);

  int k    = 0;
  int j    = 0;
  int ktmp = 0;

  printf("M: %d\n", m);
  for(int i=0; i<n; i++){
    j = (int)T[i];
//    printf("%d\n", j);
    ktmp = k;
    k = dd[k][j];
//    if(k == ktmp) k = 0;                               //(***)zapamiętanie starego "k" i sprawdzenie czy "za długo stan nie jest ten sam"
//    printf("k: %d\n", k);
    if(k==m){
      printf("|| Znaleziono na pozycji: %d\n", i-m+2); //+2 żeby pokazywało od "1" czyli "od literki"
    }
  }

  free(dd);

  return;
}

int main(){

  char nazwa_tekstu[100];
  char nazwa_wzorca[100];

  system("clear");

  printf("Program korzystający z Automatu Skończonego.\n\n");

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

  Automat(wzorzec, tekst, n, m);

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
