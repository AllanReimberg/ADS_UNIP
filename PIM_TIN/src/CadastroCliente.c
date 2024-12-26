#include "../include/CadastroCliente.h"
#include "../include/Cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Função para cadastrar um cliente
void cadastrarCliente() {
    Cliente cliente;
        printf("=========================================\n");
        printf("        PREENCHA OS DADOS CLIENTE\n");
        printf("=========================================\n");
    
    printf("\nDigite o nome do cliente: ");
    fgets(cliente.nome, 100, stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = 0;

    printf("Digite o CNPJ da empresa: ");
    fgets(cliente.cnpj, 20, stdin);
    cliente.cnpj[strcspn(cliente.cnpj, "\n")] = 0;

    printf("Digite o endereço da empresa: ");
    fgets(cliente.endereco, 100, stdin);
    cliente.endereco[strcspn(cliente.endereco, "\n")] = 0;

    FILE *arquivo = fopen("clientes.txt", "a");
    if (arquivo != NULL) {
        fprintf(arquivo, "Nome: %s\n", cliente.nome);
        fprintf(arquivo, "CNPJ: %s\n", cliente.cnpj);
        fprintf(arquivo, "Endereço: %s\n", cliente.endereco);
        fprintf(arquivo, "----------------------------------\n");
        fclose(arquivo);
        printf("\nCliente cadastrado com sucesso!\n");
    } else {
        printf("Erro ao cadastrar cliente!\n");
    }

    // Mensagem de retorno ao menu
    printf("\nVoltando ao menu anterior...");
    Sleep(2000);
    system("cls");
}
