#include "../include/AgendarVisita.h"
#include "../include/Cliente.h"
#include "../include/MenuRelatorio.h"
#include "../include/CadastroCliente.h"
#include <stdio.h>      
#include <stdlib.h>   
#include <string.h>

#define MAX_CLIENTES 100

  // Função para salvar informações do cliente
void salvarClienteEmArquivo(Cliente cliente, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "a");  // Abre o arquivo no modo de adição
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar o cliente.\n");
        return;
    }
    fprintf(arquivo, "Nome: %s\nCNPJ: %s\nEndereço: %s\n----------------------------------\n",
            cliente.nome, cliente.cnpj, cliente.endereco);
    fclose(arquivo);  // Fecha o arquivo após escrever
    printf("Cliente salvo com sucesso em %s.\n", nomeArquivo);
}

// Definição das variáveis globais
Cliente clientes[MAX_CLIENTES];
int numClientes;