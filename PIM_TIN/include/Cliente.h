#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <string.h>

#define MAX_CLIENTES 100

// Estrutura do cliente
typedef struct {
    char nome[100];
    char cnpj[20];
    char endereco[150];
} Cliente;

// Variáveis globais
extern Cliente clientes[MAX_CLIENTES];
extern int numClientes;

// Declarações das funções
int carregarClientes(Cliente clientes[]);
void listarClientes(Cliente clientes[], int numClientes);
void cadastrarCliente();
void agendarVisita();

#endif
