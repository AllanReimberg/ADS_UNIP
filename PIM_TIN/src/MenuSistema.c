#include "../include/MenuSistema.h"
#include "../include/MenuRelatorio.h"
#include "../include/Cliente.h"
#include "../include/CadastroCliente.h"
#include "../include/AgendarVisita.h"
#include "../include/VerAgendamentos.h"
#include "../include/Orcamento.h"
#include "../include/VerOrcamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h> // Para _getch()



void menusistema() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // manipulador do console
    COORD cursorPos; // armazenar a posição do cursor
    int opcao = 0;

    do {
        system("cls");
        printf("==========================================\n");
        printf("                     TIN\n");
        printf("               MENU PRINCIPAL\n");
        printf("==========================================\n");
        printf("\n1 - Cadastrar cliente\n");
        printf("2 - Relatorios\n");
        printf("3 - Agendar Visita\n");
        printf("4 - Ver agendamentos\n");
        printf("5 - Criar Orcamentos\n");
        printf("6 - Ver Orcamentos\n");
        printf("7 - Deslogar\n");
        printf("8 - Sair\n");
        printf("\n> Escolha uma opcao: ");

                // Salvar a posição atual do cursor
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        cursorPos = csbi.dwCursorPosition;

        // Adiciona a frase extra abaixo
        printf("\n\n\n@TIN - Tecnologia Implementada aos Negocios");

        // Retorna o cursor para a posição da entrada
        SetConsoleCursorPosition(hConsole, cursorPos);


        // Lógica para capturar apenas números entre 1 e 8
        while (1) {
            char ch = _getch(); // Captura um caractere sem exibir na tela
            if (ch >= '1' && ch <= '8') { 
                opcao = ch - '0'; // Converte o caractere para número
                printf("%d\n", opcao); // Mostra a opção selecionada
                break;
            }
        }

        system("cls");

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                MenuRelatorio();
                break;
            case 3:
                agendarVisita(clientes, &numClientes);
                break;
            case 4:
                verAgendamentoPorCliente();
                break;
            case 5:
                orcar();
                break;
            case 6:
                VerOrcamento();
                break;
            case 7:
                printf("\nDeslogando...");
                Sleep(2000);
                system("cls");
                return;
            case 8:
                printf("Saindo...\n");
                exit(0);
                break;
            default:
                // Nunca será alcançado devido à validação anterior
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 8);
}
