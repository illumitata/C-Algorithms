#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//zmienne globalne
#define DL 500        //długość kolejki
char nazwa[200];      //przechowuje nazwę pliku
int kod[10];
char znak;            //przechowuje czytany znak z pliku
int i;                //zmienna do iteracji w main
int n;
int m = 0;
int z = 0;

int suma1 = 0;           //suma "oryginalna"
int suma2 = 0;           //suma po kompresji
//koniec zmiennych globalnych

//struktury

  //struktura węzła
  struct Wezel{
    char lit;         //litera przechowywana w węźle
    int  ile;         //ilość wystąpień litery
    struct Wezel *lewy, *prawy, *rodzic;
    char czy;          //"flaga" do ustalenia czy dany węzeł (nie)istnieje("0"/"1")/czy jest łącznikiem"("*")
    int wart;          // 0 lewy, 1 prawy, 2 nie wiadomo
  } wezel;

  //"tabela" wyników
  struct Wynik{
    char c;           //znak przechowywany
    int  code;        //kod huffmana dla znaku
  };
//koniec struktur

/*
    --------------------------------
    Tworzenie kolejki i jej sortowanie
    --------------------------------
*/

void malokuj2(struct Wynik *kolejka[]){
  for(i=0; i<DL; i++){
    kolejka[i] = malloc(sizeof(struct Wynik));
    kolejka[i]->c = '0';                        //zakładam, że zera nie będą kodowane
    kolejka[i]->code = -1;
  }
}

void malokuj(struct Wezel *kolejka[]){
  for(i=0; i<DL; i++){
    kolejka[i] = malloc(sizeof(struct Wezel));
    kolejka[i]->lit = '0';                        //zakładam, że zera nie będą kodowane
    kolejka[i]->ile = -1;
    kolejka[i]->czy = '0';
  }
}

void stos(struct Wezel *kolejka[]){

  FILE *fp = fopen(nazwa, "r");

  do{
    znak = fgetc(fp);
    if(znak != -1 && znak != 10 && znak != 32){   //-1 = 0 czyli znakowi null
      for(i=0; i<DL; i++){
        if(znak != kolejka[i]->lit && kolejka[i]->czy == '0'){
          struct Wezel *nowy = malloc(sizeof(struct Wezel));
          nowy->lit = znak;
          nowy->ile = 1;
          nowy->rodzic = NULL;
          nowy->lewy   = NULL;
          nowy->prawy  = NULL;
          nowy->czy    = '1';
          nowy->wart   = 2;
          kolejka[n]   = nowy;
          n++;
          break;                      //uciekam z tej pętli, bo już stworzyłem nowy węzeł, oszczędzam obliczenia
        }
        else{
          if(znak == kolejka[i]->lit){
            kolejka[i]->ile++;
            break;                    //uciekam, bo już iterowałem ilość wystąpień
          }
        }
      }
    }
  }while(znak != EOF);

  fclose(fp);

 printf("stos:\n");
 for(i=0;i<10; i++) printf("%d %c %d %c\n", i, kolejka[i]->lit, kolejka[i]->ile, kolejka[i]->czy);
}

void sortuj(struct Wezel *kolejka[]){

  int   j;
  int   tmp;
  char  tmp2;
  char  tmp3;
  struct Wezel *tmpl;
  struct Wezel *tmpp;
  struct Wezel *tmpr;

  n=0;

  while(kolejka[n]->czy != '0') n++;

  n--;

  for(j=0; j<n; j++){
    for(i=0; i<n; i++){
      if((kolejka[i]->ile) > (kolejka[i+1]->ile)){
        tmp = kolejka[i]->ile;
        kolejka[i]->ile = kolejka[i+1]->ile;
        kolejka[i+1]->ile = tmp;

        tmp2 = kolejka[i]->lit;
        kolejka[i]->lit = kolejka[i+1]->lit;
        kolejka[i+1]->lit = tmp2;

        tmp3 = kolejka[i]->czy;
        kolejka[i]->czy = kolejka[i+1]->czy;
        kolejka[i+1]->czy = tmp3;

        tmpl = kolejka[i]->lewy;
        kolejka[i]->lewy = kolejka[i+1]->lewy;
        kolejka[i+1]->lewy = tmpl;

        tmpp = kolejka[i]->prawy;
        kolejka[i]->prawy = kolejka[i+1]->prawy;
        kolejka[i+1]->prawy = tmpp;

        tmpr = kolejka[i]->rodzic;
        kolejka[i]->rodzic = kolejka[i+1]->rodzic;
        kolejka[i+1]->rodzic = tmpr;
      }
    }
  }

 printf("posortowane:\n");
 for(i=0; i<10; i++) printf("%d %c %d %c\n", i, kolejka[i]->lit, kolejka[i]->ile, kolejka[i]->czy);
}
/*
    --------------------------------
    Menu wyboru, kodowanie i odkodowanie pliku
    --------------------------------
*/


/*
   idea zakodowania opiera się na tym, że w tablicę wrzucam ciąg zer i jedynek
   nie potrafię w C użyć tylko bitów, bajty są najmniejszą jednkostką długości
*/

void zakoduj(char tekst[], struct Wynik *tabela[]){

  FILE *fp = fopen(nazwa, "r");

  i = 0;

  do{
    znak = fgetc(fp);
    tekst[i] = znak;
    i++;
  }while(znak != EOF);

  fclose(fp);

  printf("\nKodowany tekst:\n");
  for(int k=0;k<i-1;k++) printf("%c",tekst[k]);        //k to iteracja, i-1 to tablica bez ostatniego znaku EOF'a

  char gotowe[9999];
  int h = 0;
  int pom = 0;

  for(int k=0; k<i-1;k++){
    for(z=0; z<DL; z++){
      if(tabela[z]->c == tekst[k]){
        pom = tabela[z]->code;
        /*if(pom==0){
          gotowe[h] = 0;
          h++;
          break;
        }*/
        do{
          if(pom%2 == 0) gotowe[h] = 0;
          else gotowe[h] = 1;
          pom = pom/2;
          pom = (int)floor(pom);
          h++;
        }while(pom>0);
        break;
      }
    }
  }

    gotowe[h] = 's';
    int nu = 0;

    for(int k=0; k<9999; k++){
      if(gotowe[k]=='s') break;
      nu++;
    }

    //printf("\n\n%d\n\n", nu);       //taka długość zakodowanego tekstu

    char gotowe2[nu];

    for(int k=0; k<nu; k++){
      gotowe2[k] = gotowe[k];
    }

    //printf("\n%d\n", gotowe2[100]);

  FILE *bin;                                           //plik binarny
  if((bin=fopen("wynik.bin", "rb+")) == NULL) {
    // nie udalo nam sie otworzyc pliku, wiec tworzymy nowy plik
    if((bin=fopen("wynik.bin", "wb+")) == NULL) {
      printf("Blad przy tworzeniu pliku !\n");
    }
  }

  //printf("\n%c %c\n", tekst[0], tekst[1]);
  //printf("\n\n\n%d %d %d %d %d %d\n\n\n", gotowe[0], gotowe2[0], gotowe[1], gotowe2[1], gotowe[2], gotowe2[2]);

  fwrite(gotowe2, sizeof(char), sizeof(gotowe2), bin);

  fclose(bin);

  return;
}

void odkoduj(char tab[], struct Wynik *tabela[]){

  long wielk;                                          //wielkość pliku
  char *buffer;
  size_t result;

  FILE *bin;                                           //plik binarny
  if((bin=fopen("wynik.bin", "r")) == NULL) {
      printf("Nie ma takiego pliku!\n");
  }

  fseek(bin , 0 , SEEK_END);
  wielk = ftell(bin);
  rewind(bin);

  buffer = (char*) malloc(sizeof(char) *wielk);
  if(buffer==NULL) puts("Bład przy wczytaniu.");

  result = fread(buffer, 1, wielk, bin);              //fread zwraca wartość równą ilości wczytanych elementów dlatego sprawdzam
  if(result!=wielk) puts("Bład przy wczytywaniu2.");

  fclose(bin);

  //printf("%ld\n", wielk);
  //printf("\n%d\n", buffer[100]);
  //odkodowanie w pętli

  printf("\nZakodowany i odczytany z pliku tekst:\n");
  for(i=0; i<wielk;i++) printf("%d", buffer[i]);      //z jakiejś przyczyny wrzuca coś na początek bufora?
  printf("\n");

//      Nie wiem dlaczego tutaj coś nie działa
  int sumaodkod[8];
  int odkod = 0;
  int bit   = 0;
  int p = 0;
  int flaga = 0;

  for(i=0; i<8; i++) sumaodkod[i] = 0;          //wyzerowanie tablicy odkodowanej
  int f = 7;                                        //zmienna do liczenia binarnego

  for(int k=0; k<wielk;k++){
    bit = (int)buffer[k];
    sumaodkod[f] = bit;
    for(i=8; i>=1; i--){
      if(sumaodkod[i]==1){
        odkod += pow(2, 8-i);
      }
    }
    for(z=0; z<DL; z++){
      if(tabela[z]->code == odkod){
        tab[p] = tabela[z]->c;
        for(i=0; i<8; i++) sumaodkod[i] = 0;
        f=7;
        flaga = 1;
        p++;
        break;
      }
    }
    odkod = 0;
    if(flaga == 1) flaga = 0;
    else f--;
  }

      puts("Odkodowany:");
      for(i=0; i<DL; i++) printf("%c",tab[i]);

  free(buffer);
  return;
}

void menu(struct Wezel *kolejka[], struct Wynik *tabela[]){

  short int wybor;
  printf("Co chcesz zrobić z utworzonym kodem?\n");
  puts("Wpisz '1', żeby zakodować plik do postaci binarnej.");
  puts("wpisz '2', żeby odkodować plik do postaci tekstowej.");
  puts("Wpisz '3', żeby zakończyć program.");

  scanf("%hd", &wybor);
  char tekst[DL];
  char tab[DL];

  switch(wybor){
    case 3:
      break;
    case 1:
      zakoduj(tekst, tabela);
      menu(kolejka, tabela);
      break;
    case 2:
      odkoduj(tab, tabela);
      menu(kolejka,tabela);
      break;
    default:
      puts("Wpisz poprawnie opcję :/");
      menu(kolejka, tabela);
      break;
  }

  return;
}
/*
    --------------------------------
    Przeszukiwanie postorder oraz policzenie kompresji
    --------------------------------
*/

void drukujTab(int arr[], int n, struct Wynik *tabela[]){
    int tmp = 0;
    int i;
    for (i = 0; i < n; ++i){
        printf("%d", arr[i]);
        if(arr[i]==1) tmp += pow(2, n-i-1);
    }

    tabela[z]->code = tmp;

    printf(" %d",tabela[z]->code);
    printf(" %c",tabela[z]->c);
    printf("\n");

    z++;
}

int lisc(struct Wezel* root, int licz, struct Wynik *tabela[]){
    if(root->lewy==NULL && root->prawy==NULL){
      suma2 += (root->ile) * licz;
      tabela[z]->c = root->lit;
      return 1;
    }
}

void drukuj(struct Wezel* jest, int kod[], int lol, struct Wynik *tabela[]){

  //printf("\n-----------------------\n");

  //if(jest->lewy!=NULL && jest->prawy!=NULL) printf("wartości lacza: %d %c %d %c\n", jest->lewy->ile, jest->lewy->lit, jest->prawy->ile, jest->prawy->lit);

  if(jest->lewy){
    kod[lol] = 0;
    drukuj(jest->lewy, kod, lol+1, tabela);
  }
  if(jest->prawy){
    kod[lol] = 1;
    drukuj(jest->prawy, kod, lol+1, tabela);
  }
  if(lisc(jest, lol, tabela)==1){                   //można usunąć ==1, by zobaczyć przebieg postorder
    printf("%c ", jest->lit);
    drukujTab(kod, lol, tabela);
  }
}

void policzkompresje(){
  printf("Suma przed kompresją:               %4d\n",suma1);
  printf("Suma po wykonanej kompresji :       %4d\n",suma2);

  float stopien = (float)suma2/(float)suma1;                  //dobrze to liczę?

  printf("Stopień kompresji za pomocą kodu:   %.8lf",stopien);

  printf("\n\n");
  return;
}
/*
    --------------------------------
    Wyszukiwanie minimum oraz budowa drzewa
    --------------------------------
*/

void minimum(struct Wezel *kolejka[]){

    struct Wezel *min;
    struct Wezel *min2;
    min  = kolejka[n];
    min2 = kolejka[n];

  for(i=n; i>=0; i--){                    //szukanie pierwszego minimalnego węzła
    if(kolejka[i]->ile < kolejka[i-1]->ile) min = kolejka[i];
  }

  for(i=n; i>=0; i--){                    //szukanie drugiego minimalnego węzła
    if(kolejka[i]->ile < kolejka[i-1]->ile) min2 = kolejka[i];
    if(kolejka[i]->lit == min->lit) min2 = kolejka[i+1];
  }

  printf("Minimum znalezione:\n");
  printf("%d %c %d %c\n", i, min->lit, min->ile, min->czy);
  printf("%d %c %d %c\n", i, min2->lit, min2->ile, min2->czy);

  struct Wezel *lacz = malloc(sizeof(struct Wezel));

  //lacz->rodzic = NULL;

  if(min->ile <= min2->ile){
    lacz->lewy   = min;
    min->rodzic  = lacz;
    min->wart    = 0;
    lacz->prawy  = min2;
    min2->rodzic = lacz;
    min2->wart   = 1;
  }
  else{
    lacz->lewy   = min2;
    min2->rodzic = lacz;
    min2->wart   = 1;
    lacz->prawy  = min;
    min->rodzic  = lacz;
    min->wart    = 0;
  }

  lacz->lit = '*';
  lacz->czy = '*';
  lacz->ile = min->ile + min2->ile;

  kolejka[0] = lacz;
  kolejka[1] = kolejka[n];
  kolejka[n] = kolejka[n+1];  //ROZWIĄZANE! może tutaj być problem w przyszłości

  n--;
  printf("wartości lacza: %d %c %d %c %d\n", lacz->lewy->ile, lacz->lewy->lit, lacz->prawy->ile, lacz->prawy->lit, lacz->lewy->rodzic->ile );
}

void buduj(struct Wezel *kolejka[], struct Wynik *tabela[]){

  while(kolejka[1]->czy != '0'){
    minimum(kolejka);
    sortuj(kolejka);
  }

//  kolejka[0] to root
  printf("wartości roota: %d %c %c %d %c\n", kolejka[0]->ile, kolejka[0]->lit, kolejka[0]->czy, kolejka[0]->lewy->wart, kolejka[0]->prawy->lit);

//policzenie kompresji zanim znikną zmienne (razy stała długość 3)
  suma1 = (kolejka[0]->ile) * 3;

  printf("\n---Wartości zakodowane huffmanem---\n");

  drukuj(kolejka[0], kod, 0, tabela);

  printf("\n");

  policzkompresje();

  menu(kolejka, tabela);

  return;
}
/*
    --------------------------------
    --------------------------------
    --------------------------------
*/

void main(){


  struct Wezel *kolejka[DL];

  struct Wynik *tabela[DL];

  printf("Podaj nazwę pliku do wczytania: ");
  scanf("%s", nazwa);

    malokuj(kolejka);
    malokuj2(tabela);
    stos(kolejka);
    sortuj(kolejka);

    buduj(kolejka, tabela);
}
