#include <stdio.h>
#include <stdlib.h>

#define DL 1000                                      //1000 węzłów to chyba odpowiednia liczba
int rep = -1;
int f   =  0;

  struct Galaz{
    int gora;
    int dol;
  };

  struct Wezel{
    int    klucz;
    int    ranga;
    struct Wezel *rodzic;
  };

  void malokuj(struct Wezel *lista[]){
    for(int i=0; i<DL; i++){
      lista[i] = malloc(sizeof(struct Wezel));
      lista[i]->klucz   = -1;                        //zakładam, że -1 nie będą kodowane
      lista[i]->ranga   =  0;
    }
    return;
  }

  void malokuj2(struct Galaz *drzewo[]){
    for(int i=0; i<DL; i++){
      drzewo[i] = malloc(sizeof(struct Galaz));
      drzewo[i]->gora   = -1;                        //zakładam, że -1 nie będą kodowane
      drzewo[i]->dol    = -1;
    }
    return;
  }

  void MakeSet(struct Wezel *lista[], int k){
    struct Wezel *nowy = malloc(sizeof(struct Wezel));
    nowy->klucz  = k;
    nowy->ranga  = 0;
    nowy->rodzic = nowy;

    lista[k] = nowy;

    return;
  }

  int FindSet(struct Wezel *lista[], int k){
    //printf("\nklucz rodzica: %d\n", lista[k]->rodzic->klucz);
    if(lista[k]->rodzic == NULL) return k;                     //gdy nie ma rodzica
    if(lista[k]->klucz != lista[k]->rodzic->klucz){
      k = lista[k]->rodzic->klucz;
      rep = FindSet(lista, k);
      return rep;                                              //zwraca indeks reprezentanta
    }
  }

  void Union(struct Wezel *lista[], int x, int y){

    int rep1 = FindSet(lista, x);
    int rep2 = FindSet(lista, y);

    if(lista[rep1]->ranga > lista[rep2]->ranga){
      *lista[rep2]->rodzic = *lista[rep1];
    }
    else{
      *lista[rep1]->rodzic = *lista[rep2];
      if(lista[rep1]->ranga == lista[rep2]->ranga){
        int tmp = lista[rep2]->ranga;
        tmp = tmp + 1;
        lista[rep2]->ranga = tmp;
      }
    }

    return;
  }

    void graf(struct Wezel *lista[]){
      struct Galaz *drzewo[DL];
      malokuj2(drzewo);
      int g          = 0;
      int korzen     = 0;
      int korzentmp  = 0;

      for(int k=0; k<DL; k++){
          if(lista[k]->ranga >= 0 && lista[k]->klucz != -1){
            korzen = FindSet(lista, k);
            printf("\n%d <-\n", korzen);
              for(int h=0; h<DL; h++){
                korzentmp = FindSet(lista, h);
                  if(korzentmp == korzen){
                    drzewo[g]->gora = korzentmp;
                    drzewo[g]->dol  = h;
                    if(drzewo[g]->dol != drzewo[g]->gora) printf("%d ", drzewo[g]->dol);
                    //^^^ można usunąć if, będzie drukował się dosłownie ze wskazaniem na siebie
                    g++;
                  }
              }
            printf("\n");
          }
      }
    return;
    }

  void WrocDoDomu(struct Wezel *lista[], int k){
    printf("%d ", k);
    if(lista[k] == lista[k]->rodzic){
      printf("\n\n");
      return;
    }
    else WrocDoDomu(lista, lista[k]->rodzic->klucz);
  }

  void sciezki(struct Wezel *lista[]){
    for(int k=0; k<DL; k++){
      if(lista[k]->rodzic != NULL) WrocDoDomu(lista, k);
    }

    return;
  }

  void menu(struct Wezel *lista[]){
    short int   wybor;
    int         podanyklucz1 = -1;
    int         podanyklucz2 = -1;

    puts("Wpisz '1', żeby wykonać MakeSet.");
    puts("Wpisz '2', żeby wykonać Union.");
    puts("Wpisz '3', żeby wykonać FindsetX == FindsetY.");
    puts("Wpisz '4', żeby wyświetlić graficzne drzewo.");
    puts("Wpisz '5', żeby zakończyć program.");
    printf("\n");

    scanf("%hd", &wybor);

    switch(wybor){
      case 1:
        printf("\nPodaj klucz,który chcesz dodać: ");
        scanf("%d", &podanyklucz1);
        MakeSet(lista, podanyklucz1);
        printf("\n");
        menu(lista);
        break;
      case 2:
        printf("\nPodaj pierwszy klucz: ");
        scanf("%d", &podanyklucz1);
        printf("\n");
        printf("\nPodaj drugi klucz   : ");
        scanf("%d", &podanyklucz2);
        Union(lista, podanyklucz1, podanyklucz2);
        printf("\nPołączono zbiory...\n\n");
        menu(lista);
        break;
      case 3:
        printf("\nPodaj klucz X: ");
        scanf("%d", &podanyklucz1);
        printf("\nPodaj klucz Y: ");
        scanf("%d", &podanyklucz2);
        printf("\n");
        int wynik1  = FindSet(lista, podanyklucz1);
        int wynik2  = FindSet(lista, podanyklucz2);
        printf("\n\nKlucz X ma reprezentacje: %d\n", wynik1);
        printf("Klucz Y ma reprezentacje: %d\n", wynik2);
        if(wynik1 == wynik2) printf("\nOba zbiory znajdują się w tej samej rodzinie.\n\n");
        else printf("\nZbiory nie znajdują się w tej samej rodzinie.\n\n");
        menu(lista);
        break;
      case 4:
        printf("\nPoszczególne ścieżki w grafie:\n");
        sciezki(lista);                                   //pokazuje ścieżki, kompresowane
        printf("\nReprezentacja drzewiasta:\n\n");
        graf(lista);                                      //graf również podlega natychmiastowej kompresji
        printf("\n");
        menu(lista);
        break;
      case 5:
        break;
      default:
        puts("Wybierz opcję od 1 do 4.");
        menu(lista);
        break;
    }
  }


  void main(){
    struct Wezel *lista[DL];

    malokuj(lista);
    menu(lista);

  }
