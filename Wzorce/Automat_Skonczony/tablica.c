//funckja zwracająca tablicę znaków wczytaną na podstawie podanego pliku tekstowego

#include <stdio.h>
#include <stdlib.h>
#include "tablica.h"

static int i = 0;

char* przepisz(char* nazwa, int dlugosc){  //przepisanie tablicy do tablicy

    char znak;
    char* tab = (char*) malloc(sizeof(*tab) * dlugosc);
//  int i = 0;   postanowiłem zmienić ją na globalną, żeby funckja niżej zwracała długość tekstu
    i = 0;

    FILE *fp = fopen(nazwa, "r");

    do{
      znak = fgetc(fp);
      if(znak != 13 && znak != 10 && znak != EOF && znak != 32 && znak != 12){   //ignorowanie nowych linii oraz początku i końca tekstu(czy koniecznie?)
        tab[i] = znak;
        i++;
      }
    }while(znak != EOF);

    fclose(fp);

    return tab;
}

int ileznakow(){
    return i;
}
