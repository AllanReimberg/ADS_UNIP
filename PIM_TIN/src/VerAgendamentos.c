#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "../include/AgendarVisita.h"

void verAgendamentoPorCliente() {
    char nomeCliente[100];
    printf("\n=========================================\n");
    printf("           VERIFICAR AGENDAMENTOS\n");
    printf("=========================================\n");
    printf("\nDigite o nome do cliente para verificar o agendamento: ");
    fgets(nomeCliente, sizeof(nomeCliente), stdin);
    nomeCliente[strcspn(nomeCliente, "\n")] = '\0'; // Remove o '\n' do final da string

    FILE *arquivoAgendamentos = fopen("Agendamentos.txt", "r");
    if (arquivoAgendamentos == NULL) {
        printf("Erro ao abrir o arquivo Agendamentos.txt ou nenhum agendamento registrado.\n");
        return;
    }

    char linha[200];
    int encontrado = 0; // Flag para verificar se encontrou o agendamento

    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivoAgendamentos)) {
        if (strstr(linha, nomeCliente) != NULL) {  // Se o nome do cliente for encontrado
            printf("\nAgendamento encontrado para %s:\n", nomeCliente);
            printf("%s", linha);  // Exibe o nome do cliente

            // Lê a próxima linha para exibir a data
            if (fgets(linha, sizeof(linha), arquivoAgendamentos)) {
                printf("%s", linha);  // Exibe a data da visita
            }
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nNenhum agendamento encontrado para o cliente %s.\n", nomeCliente);
    }
    printf ("\n- Pressione Enter para voltar -");
    fclose(arquivoAgendamentos);    
    getchar();
    system("cls");
}

