#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>  // Para pegar a data atual e calcular a validade do orçamento

#define MAX_NOME 100

void orcar() {
    char nomeCliente[MAX_NOME];
    printf("\n=========================================\n");
    printf("            AREA DE ORÇAMENTO\n");
    printf("=========================================\n");
    printf("\nDigite o nome do cliente: ");
    fgets(nomeCliente, MAX_NOME, stdin);
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
        printf("- Cliente '%s' não encontrado no cadastro - \n", nomeCliente);
        return;
    }

    // Cliente encontrado, prossegue para salvar o orçamento
    printf("\n- Cliente encontrado! Prosseguindo com o orçamento -\n");

    FILE *arquivoOrcamentos = fopen("Orcamentos.txt", "a");
    if (arquivoOrcamentos == NULL) {
        printf("Erro ao abrir o arquivo Orcamentos.txt!\n");
        return;
    }

    // Entrar com os dados do orçamento
    float valorOrcamento;
    char motivo[200];

    printf("\nDigite o valor do orçamento: ");
    scanf("%f", &valorOrcamento);
    getchar();  // Para consumir o caractere '\n' deixado pelo scanf

    printf("Digite o motivo do orçamento: ");
    fgets(motivo, sizeof(motivo), stdin);
    motivo[strcspn(motivo, "\n")] = 0; // Remove o '\n'

    // Obter a data atual
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    // Formatar a data atual
    char dataCriacao[20];
    snprintf(dataCriacao, sizeof(dataCriacao), "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Calcular a data de validade (60 dias após a data de criação)
    tm.tm_mday += 60;  // Adiciona 60 dias
    mktime(&tm);  // Ajusta a data corretamente após adicionar 60 dias
    char dataValidade[20];
    snprintf(dataValidade, sizeof(dataValidade), "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Salvar os dados no arquivo Orcamentos.txt
    fprintf(arquivoOrcamentos, "Nome: %s\nValor do Orçamento: %.2f\nMotivo: %s\nData de Criação: %s\nData de Validade: %s\n----------------------------------\n", 
            nomeCliente, valorOrcamento, motivo, dataCriacao, dataValidade);
    fclose(arquivoOrcamentos);

    printf("\nOrçamento salvo com sucesso!\n");
    printf("Orçamento válido por 60 dias a partir de: %s\n", dataCriacao);

    Sleep(2000);  // Pausa de 2 segundos
    system("cls"); // Limpa a tela
}