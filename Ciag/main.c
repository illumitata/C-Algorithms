#include <stdio.h>
#include <string.h>

int i, j, m, n, a, c[100][100];
char x[100], y[100], b[100][100];

void PrintLcs(int i,int j){
    if(i==0 || j==0){
        return;
    }
    if(b[i][j] == 'c'){
        PrintLcs(i-1,j-1);
        printf("%c",x[i-1]);
    }
    else if(b[i][j]=='u'){
        PrintLcs(i-1,j);
    }
    else{
        PrintLcs(i,j-1);
    }
}

void lcsdl(void){
    m = strlen(x);
    n = strlen(y);
    for(i = 0; i <= m; i++){
        c[i][0]=0;
    }
    for(i = 0; i<= n; i++){
        c[0][i] = 0;
    }
    for(i = 1; i <= m; i++){
        for(j = 1; j <= n; j++){
            if(x[i-1] == y[j-1]){
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = 'c';
            }
            else if(c[i-1][j] >= c[i][j-1]){
                c[i][j] = c[i-1][j];
                b[i][j] = 'u';
            }
            else{
                c[i][j] = c[i][j-1];
                b[i][j] = 'l';
            }
        }
    }
    PrintLcs(m,n);
 }

int main(void){
    printf("Podaj pierwszy ciąg:\n");
    gets(x);
    printf("Podaj drugi ciąg:\n");
    gets(y);
    printf("Wynik algorytmu: \n");
    lcsdl();
    printf("\n");

    return 0;
}
