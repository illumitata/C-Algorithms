#include <stdio.h>
#include <math.h>

int i, j, dl;       //i do iteracji
int obieg;          //obieg dzielenia na piątki
int k;              //szukany k-wyraz w problemie
int dlr;            //"rzeczywista" długoś tablicy w C
int tab2[5];        //mniejsza tablica w której będą robione mediany (z założenia algorytmu 5)
int mm;             //mediana median
int x = 0;          //szukany wyraz k wychodzący z funkcji

void wstaw(int tab[], int n){
      int tmp;
      for(j=n-1; j>=0; j--){
        tmp=tab[j];
        i=j+1;
        while((i<=n)&&(tmp>tab[i])){
          tab[i-1]=tab[i];
          i++;
        }
        tab[i-1]=tmp;
      }

printf("To Twoja posortowana tablica przez wstawianie:\n");
  for(i=0; i<=n; i++) printf("%4d", tab[i]);
printf("\n");
}

int Mediana(int tab2[], int m){                      //w tablicy od zera modulo jest tak jakby "odwrócone"
            if((m%2)==0){                            //zwracanie środkowego wyrazu dla tablicy piątek
                m = floor((m+1)/2);
                m = tab2[m];
                return m;
            }
            else{                                    //łapiemy dolną medianę (tak było tłumaczone przy tablicy w dniu sprawdzianu!)
                m = floor(m/2);
                m = tab2[m];
                return m;
            }
}

int partition(int *tab, int n, int x){ //zwraca ilość liczb na lewo od pivota czyli mediany median
  // wcześniej umieściłem dlatego pivota na końcu
  for(int i = 0; i < n; i++) {
	if(tab[i] == x) {
	  tab[i] = tab[n-1];
	  tab[n-1] = x;
    }
  }

  int i = 0;
  for(int j = 0; j < (n-1); j++) {
	if(tab[j] <= x) {
	  int tmp = tab[j];
	  tab[j] = tab[i];
	  tab[i] = tmp;
	  i++;
	}
  }

  //pivot znowu na poprawne miejsce
  tab[n-1] = tab[i];
  tab[i] = x;

  return i;
}

int MagicznePiatki(int *tab, int u){
  //pewnie przy rekurencji się zapętli więc dać tu if(dl==1) :)
  int a, b, reszta;
  int c = 0;               //potrzebne do iteracji w pętli niżej
  int r = 0;
  int q = 0;               //r i q zmienne na obieg median

  if(dl==1) return tab[0];

  int dlr= dl - 1;

  if(dl <= 10){
    wstaw(tab, dl-1);
    x = tab[u];
    return x;
  }
  else{

  reszta = dl%5;                            //sprawdzamy, czy tablica dzieli się na równe piątki

  obieg = floor(dl/5);

  if(reszta==0) q = obieg;
  else q = obieg + 1;

  int med[q];

  obieg = dl/5;
    for(a=0; a<obieg; a++){                //wpisywanie do tablicy b pożądanej piątki
        for(b=(a*5);b<((a+1)*5);b++){      //b<(obieg*5) powodawało stack smashing, teraz bezbłędnie
          tab2[c]=tab[b];
          c++;
        }
      wstaw(tab2, c-1);
      med[r]=Mediana(tab2, c-1);
      r++;
      c = 0;
    }

  if(reszta!=0){                          //dodatkowy for dla liczb nie łapiących się w piątkę
    for(a=dlr; a>=obieg*5; a--){
        tab2[c]=tab[a];
        c++;
    }
    wstaw(tab2, reszta-1);
    med[r]=Mediana(tab2, reszta-1);	  //reszta-1 to długość wystającej tablicy w realia C
    r++;
    c=0;
  }

printf("\nTablica median: \n");
for(i=0; i<q; i++) printf("%4d", med[i]);
printf("\n\n");

int dlpom = dl;                          //Tutaj się psuło! powód dl było gubione na rzecz q
dl = q;
mm = MagicznePiatki(med, ceil((q-1)/2)); //rekurencyjnie mediana median (jest 5:06)

dl = dlpom;

printf("\nMediana median: %d\n", mm);

printf("\n\nTo Twoja tablica w tym momencie: \n");
for(i=0; i<=dlr; i++) printf ("%4d", tab[i]);
printf("\n\n");

int tempi=0;
int tmp=0;
i=0;
while(i<=dlr){                         //szukanie indeksu mediany median
  if(tab[i]==mm){
    tempi=i;
    i++;
  }
  else i++;
}

//przygotowanie do partycjonwania
    tmp = tab[dlr];
    tab[dlr] = tab[tempi];
    tab[tempi] = tmp;

                                                                                //Algorytm Hoara!!! dlaczego mi się nie udaje
printf("\n\nTo Twoja tablica w tym momencie(przed partycjonowaniem): \n");
for(i=0; i<=dlr; i++) printf ("%4d", tab[i]);
printf("\n\n");

int p = partition(tab, dlr+1, mm);    //miejsce podziału czyli miejsce mediany median

printf("\n\nTo Twoja tablica w tym momencie: \n");
for(i=0; i<=dlr; i++) printf ("%4d", tab[i]);
printf("\n miejsce podziału liczone od zera : %4d \n\n", p);

  if(p == u) {
	     return mm;
  }
  else if (u < p) {
       dl = p;
	     return MagicznePiatki(tab, u);
  }
  else {
       dl = dl - p;
       return MagicznePiatki(tab + p, u - p);                                   //ostatnia poprawka jest (03:01) wtorek
}


}//koniec else
}//koniec funkcji

void main(){

    printf("\nWitaj w problemie, podaj długość tablicy (ilość elementów licząc od 1) \nz jakiej chcesz wybrać k-ty element:\n");
    scanf("%d", &dl);

    //dlr = dl - 1; //przeniesienie długości tablicy na realia C

    int tab[dl-1];           //tablica ze wszystkimi liczbami

    printf("\nPodaj k czyli szukany element: \n");
    scanf("%d", &k);

    k = k - 1;              //dostosowanie do realiów C

    if(k>dl) printf("\nPodałeś za duże k.\n");
    else{

    printf("\nA teraz uzupełnij tablicę wyrazami: \n");
    for(i=0; i<dl; i++) scanf("%d", &tab[i]);

    printf("\n\nTo Twoja tablica: \n");
    for(i=0; i<dl; i++) printf ("%4d", tab[i]);
    printf("\n\n");

    printf("Przechodzimy teraz do rozwiązywania problemu... \nJeśli Twoja tablica posiada mniej lub równo 10 wyrazów potraktujemy ją tylko prostym sortowaniem.\n\n");

    x = MagicznePiatki(tab, k);

    printf("\n\nA to szukany k-ty wyraz: %4d \n\n", x);

  }
}
