#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "../include/Login.h"
#include "../include/CriarRelatorio.h"

// Suponhamos que você tenha o nome do usuário logado armazenado aqui
extern char usuarioAtual[100];  // Variável global que armazena o nome do usuário logado

void verificarEditarRelatorio() {
    char nomeCliente[100];
    printf("\n=========================================\n");
    printf("        VERIFICAR/EDITAR RELATORIO\n");
    printf("=========================================\n");

    // Solicita o nome do cliente
    printf("\nDigite o nome do cliente: ");
    fgets(nomeCliente, 100, stdin);
    nomeCliente[strcspn(nomeCliente, "\n")] = 0; // Remove o '\n'

    // Criar nome do arquivo de relatório do cliente
    char nomeArquivo[150];
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%s_relatorio.txt", nomeCliente);

    // Tentar abrir o arquivo de relatório para leitura
    FILE *arquivoRelatorio = fopen(nomeArquivo, "r");
    if (arquivoRelatorio == NULL) {
        printf("Relatório do cliente '%s' não encontrado!\n", nomeCliente);
        return;
    }

    // Exibir o conteúdo do relatório existente
    char linha[500];
    printf("\n - Relatório(s) existente(s) para o cliente - %s\n", nomeCliente);
    while (fgets(linha, sizeof(linha), arquivoRelatorio)) {
        printf("%s", linha);
    }

    // Perguntar ao usuário se deseja adicionar informações
    char opcao;
    printf("\n> Deseja adicionar um update ao relatório? (S/N): ");
    scanf(" %c", &opcao);
    getchar(); // Limpar o buffer

    if (opcao == 'S' || opcao == 's') {
        // Reabrir o arquivo em modo de acréscimo ('a')
        arquivoRelatorio = fopen(nomeArquivo, "a");
        if (arquivoRelatorio == NULL) {
            printf("Erro ao abrir o arquivo de relatório para adicionar informações!\n");
            return;
        }

        // Solicitar a descrição a ser adicionada
        char descricaoAdicional[500];
        printf("\nDigite a descrição adicional para o relatório: ");
        fgets(descricaoAdicional, 500, stdin);
        descricaoAdicional[strcspn(descricaoAdicional, "\n")] = 0; // Remove o '\n'

        // Obter a data e hora atual
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char dataHora[20]; // Formato DD/MM/AAAA HH:MM:SS
        snprintf(dataHora, sizeof(dataHora), "%02d/%02d/%04d %02d:%02d:%02d", 
                 tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
                 tm.tm_hour, tm.tm_min, tm.tm_sec);

        // Adicionar a descrição e a data/hora no arquivo
        fprintf(arquivoRelatorio, "\n\n------------------------------------\n");
        fprintf(arquivoRelatorio, "Update feito em: %s\n", dataHora);
        fprintf(arquivoRelatorio, "Descrição adicional: %s\n", descricaoAdicional);

        // Registrar quem fez a alteração (auditor) - Usando o nome do usuário logado
        fprintf(arquivoRelatorio, "Alterado por: %s\n", usuarioAtual);  // Usa a variável global usuarioAtual
        fprintf(arquivoRelatorio, "------------------------------------\n");

        printf("\nInformação adicionada ao relatório com sucesso!\n");

        // Usar Sleep dependendo do sistema operacional (Windows ou Linux)
        #ifdef _WIN32
            Sleep(3000); // Pausa de 3 segundos (Windows)
        #else
            sleep(3); // Pausa de 3 segundos (Linux)
        #endif

        system("cls"); // Limpar a tela após a operação
        fclose(arquivoRelatorio);
    } else {
        printf("\nNenhuma alteração foi feita no relatório.\n");
    }
}
