#include <stdio.h>
#include <stdlib.h>
#include <time.h>

////////////////////////////////////////////////////

#define DL 100

  typedef struct Punkt{
    int    klucz;                //nazwa-numer wierzchołka
    char   kolor;                //kolor 's' szary lub 'b' biały
    struct Punkt *lista[];       //tablica z biegnącymi od punktu krawędziami == do czego ten punkt jest skierowany
  }Punkt;

  void malokuj(struct Punkt *lista[]){
    for(int i=0; i<DL; i++){
      lista[i] = malloc(sizeof(struct Punkt));
      lista[i]->klucz   = -1;                        //zakładam, że -1 nie będą kodowane
      lista[i]->kolor   = 'b';
      for(int a=0; a<DL; a++){
        lista[i]->lista[a] = malloc(sizeof(struct Punkt));
        lista[i]->lista[a]->klucz = -1;
        lista[i]->lista[a]->kolor = 'b';
      }
    }
    return;
  }

  void malokujkolejke(struct Punkt *kolejka[]){
    for(int i=0; i<DL; i++){
      kolejka[i] = malloc(sizeof(struct Punkt));
      kolejka[i]->klucz   = -1;                        //zakładam, że -1 nie będą kodowane
      kolejka[i]->kolor   = 'b';
      for(int a=0; a<DL; a++){
        kolejka[i]->lista[a] = malloc(sizeof(struct Punkt));
        kolejka[i]->klucz   = -1;                        //zakładam, że -1 nie będą kodowane
        kolejka[i]->kolor   = 'b';
      }
    }
    return;
  }

  void UstawBiale(struct Punkt *lista[]){
    for(int i=1; i<DL; i++){
      lista[i]->kolor   = 'b';
      for(int a=1; a<DL; a++){
        if(lista[i]->lista[a]->kolor == 's') lista[i]->lista[a]->kolor = 'b';
      }
    }
    return;
  }

//////////////////////////////////////////////////

static int w = 0;

void SpiszGraf(char* nazwa, struct Punkt *lista[]){  //przepisanie pliku reprezentacji listowej grafu

    int licznik = 0;
    int znak;
    int tmp;
    int i = 0;

    FILE *fp = fopen(nazwa, "r");

    if (fp == NULL){
        perror("Nie udalo sie otworzyc pliku grafu!\n");
        return;
    }else{
      w = (fgetc(fp) + 2)%10;
      do{
        znak = fgetc(fp);
        //printf("ALOHA\n");
        if(znak != 13 && znak != 10 && znak != EOF && znak != 32){   //ignorowanie nowych linii oraz początku i końca tekstu(czy koniecznie?)
          znak = (znak+2)%10;
          if(licznik==0){
            lista[znak]->klucz = znak;
            tmp = znak;
            licznik++;
          }
          else{
            lista[znak]->klucz = znak;
            lista[tmp]->lista[znak] = lista[znak];
            licznik--;
          }
        }
      }while(znak != EOF);
    }

          fclose(fp);
          return;
      }

int IleWierzcholkow(){
    return w;
}

//////////////////////////////////////////////////////////////

void DFS(struct Punkt *lista[], int v){

int t = 0;

  lista[v]->kolor = 's';
  printf("%d ", lista[v]->klucz);

  for(t=1; t<=w; t++){
    if( lista[v]->lista[t]->klucz > -1 && lista[v]->lista[t]->klucz < w+1 ){
      if(lista[v]->lista[t]->kolor == 'b'){
        DFS(lista, t);
      }
    }
  }

  return;
}

void BFS(struct Punkt *lista[], int v){

  struct Punkt *kolejka[DL];

  malokujkolejke(kolejka);

  int tt = 1;
  int t = 1;
  int tmp = 1;
  int p = 1;
  int dlkolejki = 1;            //długość kolejki

  lista[v]->kolor = 's';
  printf("%d ", lista[v]->klucz);

  kolejka[1] = lista[v];

  while(dlkolejki != 0){//kolejka[1]->klucz!=-1){
        tt = kolejka[1]->klucz;
        kolejka[1]->klucz = -1;
        kolejka[1]->kolor = 'b';
        dlkolejki--;

        for(p=2; p<DL; p++) kolejka[p-1] = kolejka[p];

        for(t=1; t<=w; t++){             // można użyć (t=w; t>=1; t--) bez różnicy dla algorytmu
          if( lista[tt]->lista[t]->klucz > -1 && lista[tt]->lista[t]->klucz < w+1 ){
            if(lista[tt]->lista[t]->kolor == 'b'){
              printf("%d ", lista[t]->klucz);
              lista[t]->kolor = 's';
              dlkolejki++;
              //for(p=1; p<DL; p++) kolejka[p+1] = kolejka[p]; (***) w tym leżał problem
              kolejka[dlkolejki] = lista[t];
            }
        }
      }
  }

  return;
}

//////////////////////////////////////////////////////////////
int main(){

char nazwa_grafu[100];

system("clear");

printf("\t\t||| Program przeszukujący graf skierowany |||\n\n");

printf("\tPodaj plik z którego chcesz odczytać graf:\t");
scanf("%s", nazwa_grafu);

struct Punkt *lista[DL];

malokuj(lista);

SpiszGraf(nazwa_grafu, lista);

int wierzcholki = IleWierzcholkow();
printf("\nZnaleziono %d wierzchołków.\n\n", wierzcholki);

for(int k=1; k<=w; k++){
  for(int i=1; i<=w; i++){
    if(lista[k]->klucz != -1 &&( lista[k]->lista[i]->klucz > -1 && lista[k]->lista[i]->klucz < w+1))
    printf("Znaleziona krawędź grafu: %d %d\n", lista[k]->klucz, lista[k]->lista[i]->klucz);
    //lista[k]->kolor, lista[k]->lista[i]->kolor);
  }
}

int szukany;

printf("Podaj wierzchołek od którego chcesz zacząć szukanie w głąb: ");
scanf("%d", &szukany);
printf("\n\nWyszukane przejście w grafie:\n");
DFS(lista, szukany);

  UstawBiale(lista);

printf("\n\nPodaj wierzchołek od którego chcesz zacząć szukanie wszerz: ");
scanf("%d", &szukany);
printf("\n\nWyszukane przejście w grafie:\n");
BFS(lista, szukany);

printf("\n\n");
return 0;
}
