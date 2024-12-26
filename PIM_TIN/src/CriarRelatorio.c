#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <time.h>
#include "../include/Login.h"

// Função para capturar a opção diretamente e mudar de tela
int CapturarOpcaoDireta() {
    int opcao = 0;
    while (1) {
        char ch = getch(); // Lê a tecla pressionada
        if (ch >= '1' && ch <= '3') { // Aceita apenas '1', '2' ou '3'
            opcao = ch - '0'; // Converte o caractere para número
            printf("%c\n", ch); // Exibe o número selecionado
            break;
        }
    }
    return opcao;
}

// Função para criar o relatório
void criarRelatorio() {
    char nomeCliente[100];
    printf("\n=========================================\n");
    printf("           ÁREA DE RELATÓRIOS\n");
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
        Sleep(2000);
        system("cls");
        return;
    }

    printf("\nCliente encontrado! Prosseguindo com a criação do relatório.\n");

    // Criar nome do arquivo para o cliente
    char nomeArquivo[150];
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%s_relatorio.txt", nomeCliente);

    // Criar ou abrir o arquivo do relatório
    FILE *arquivoRelatorio = fopen(nomeArquivo, "a");
    if (arquivoRelatorio == NULL) {
        printf("Erro ao criar o arquivo do relatório '%s'!\n", nomeArquivo);
        return;
    }

    char descricaoRelatorio[500];
    printf("\n> Digite a descrição do relatório: ");
    fgets(descricaoRelatorio, 500, stdin);
    descricaoRelatorio[strcspn(descricaoRelatorio, "\n")] = 0; // Remove o '\n'

    // Obter data e horário automaticamente
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char data[11]; // Formato DD/MM/AAAA
    char horario[10]; // Formato HH:MM
    snprintf(data, sizeof(data), "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    snprintf(horario, sizeof(horario), "%02d:%02d", tm.tm_hour, tm.tm_min);

    // Escrever os dados no arquivo
    fprintf(arquivoRelatorio, "RELATÓRIO: %s\n", nomeCliente); // Nome da empresa
    fprintf(arquivoRelatorio, "Relatório criado em: %s às %s\n", data, horario);
    fprintf(arquivoRelatorio, "Descrição: %s\n", descricaoRelatorio);
    fprintf(arquivoRelatorio, "Auditor: %s\n", usuarioAtual);
    fprintf(arquivoRelatorio, "----------------------------------\n");
    fclose(arquivoRelatorio);
    
    printf("\nRelatório salvo com sucesso no arquivo: %s\n", nomeArquivo);
    printf("\nNota: Este relatório é válido por 6 meses.\n");

    Sleep(5000);
    system("cls");
}
