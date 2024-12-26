#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "../include/Orcamento.h"

void VerOrcamento() {
    char nomeCliente[100];
    printf("\n=========================================\n");
    printf("           VERIFICAR ORCAMENTOS\n");
    printf("=========================================\n");
    printf("\nDigite o nome do cliente para verificar o Orcamento: ");
    fgets(nomeCliente, sizeof(nomeCliente), stdin);
    nomeCliente[strcspn(nomeCliente, "\n")] = '\0'; 

    FILE *arquivoOrcamentos = fopen("Orcamentos.txt", "r");
    if (arquivoOrcamentos == NULL) {
        printf("Erro ao abrir o arquivo Orcamentos.txt ou nenhum Orcamento registrado.\n");
        return;
    }

    char linha[200];
    int encontrado = 0; 

   
    while (fgets(linha, sizeof(linha), arquivoOrcamentos)) {
        if (strstr(linha, nomeCliente) != NULL) { 
            printf("\nOrcamento encontrado para %s:\n", nomeCliente);
            printf("%s", linha);  

          
            if (fgets(linha, sizeof(linha), arquivoOrcamentos)) {
                printf("%s", linha); 
            }
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nNenhum orcamento encontrado para o cliente %s.\n", nomeCliente);
    }
    printf ("\n- Pressione Enter para voltar -");
    fclose(arquivoOrcamentos);    
    getchar();
    system("cls");
}