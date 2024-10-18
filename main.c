#include <stdio.h>

int main() 
{
//Declaração de variaveis inteiras 
   int i=0, j=0, soma=0;
    //Declaração de matriz vetorial
    int mat[2][2];
//Primeiro laço
for(i=0; i<2; i++)
    //Sublaço
    for(j=0; j<2; j++)
        {
            mat[i][j] = i+j;
            soma= soma + mat[i][j];
        }
//Segundo laço
for (i=0; i<2;i++)

    //Sublaço
        for(j=0;j<2;j++)
            {
                printf("%d", mat[i][j]);
            }
        printf("\n");

    printf("\nSoma = %d", soma);

    return 0;
}