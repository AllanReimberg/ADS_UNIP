#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../include/Cliente.h"
#include "../include/CriarRelatorio.h"
#include "../include/VerificarEditarRelatorio.h"

void MenuRelatorio() {
    int opcao;
    do {
        printf("=========================================\n");
        printf("            AREA DE RELATORIOS\n");
        printf("=========================================\n");
        printf("\n1 - Criar novo relatório\n");
        printf("2 - Verificar ou Acrescentar ao Relatório\n");
        printf("3 - Voltar\n");
        printf("\n> Escolha uma opção e pressione Enter: ");
        scanf("%d", &opcao);
        printf("\n \n \n@TIN - Tecnologia Implementada aos Negocios");
        getchar();
        system("cls");
        
        switch (opcao) {
            case 1:
                criarRelatorio();
                break;
            case 2:
                verificarEditarRelatorio();
                break;
            case 3:
                printf("\nVoltando ao menu principal...\n");
                Sleep(1500);
                system("cls");
                break;
            default:
                printf("O\npção inválida! Tente novamente.\n");
                Sleep(1500);
                system("cls");
        }
    } while (opcao != 3);
}