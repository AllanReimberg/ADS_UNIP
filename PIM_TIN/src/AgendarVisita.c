#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "../include/Login.h"

#define MAX_NOME 100

void agendarVisita() {
    char nomeCliente[100];
    printf("=========================================\n");
    printf("     AREA DE AGENDAMENTO DE VISITA\n");
    printf("=========================================\n");
    printf("\nDigite o nome do cliente: ");
    fgets(nomeCliente, 100, stdin);
    nomeCliente[strcspn(nomeCliente, "\n")] = 0; // Remove o '\n'

    // Verificar se o cliente existe em clientes.txt
    FILE *arquivoClientes = fopen("clientes.txt", "r");
    if (arquivoClientes == NULL) {
        printf("Erro ao abrir o arquivo clientes.txt!\n");
        return;
    }

    char linha[200];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivoClientes)) {
        if (strstr(linha, nomeCliente) != NULL) {
            encontrado = 1;
            break;
        }
    }
    fclose(arquivoClientes);

    if (!encontrado) {
        printf("Cliente '%s' não encontrado no cadastro.\n", nomeCliente);
        Sleep (2000);
        system ("cls");
        return;
    }

    // Cliente encontrado, prossegue para salvar o agendamento
    printf("\nCliente encontrado! Prosseguindo com o agendamento.\n");
    
    FILE *arquivoAgendamentos = fopen("Agendamentos.txt", "a");
    if (arquivoAgendamentos == NULL) {
        printf("Erro ao abrir o arquivo Agendamentos.txt!\n");
        return;
    }

    char dataVisita[50];
    printf("\nDigite a data da visita (formato DD/MM/AAAA): ");
    fgets(dataVisita, 50, stdin);
    dataVisita[strcspn(dataVisita, "\n")] = 0; // Remove o '\n'

    fprintf(arquivoAgendamentos, "Nome: %s\nData da Visita: %s\n----------------------------------\n", 
            nomeCliente, dataVisita);
    fclose(arquivoAgendamentos);

    printf("\nAgendamento salvo com sucesso!\n");
    Sleep(2000);
    system("cls"); 
}
