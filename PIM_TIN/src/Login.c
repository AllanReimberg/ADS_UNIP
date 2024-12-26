#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include "../include/MenuSistema.h"

#define MAX_SENHA 6
#define MAX_LOGIN 50

char usuarioAtual[100];

// Função para validar o usuário e senha
int Usuario(FILE *file, char *user, char *senha) {
    char tmpLogin[MAX_LOGIN];
    char tmpSenha[MAX_SENHA];

    while (fscanf(file, "%s %s", tmpLogin, tmpSenha) == 2) {
        if (strcmp(tmpLogin, user) == 0 && strcmp(tmpSenha, senha) == 0) {
            return 1; 
        }
    }
    return 0;
}

// Função para criar a senha, usando * para ocultar caracteres e permitir backspace
char* CriaSenha() {
    int i = 0;
    char *senha = (char*)malloc(MAX_SENHA + 1);
    if (senha == NULL) {
        printf("Erro de memória!\n");
        exit(1);
    }

    printf("Senha: ");
    while (1) {
        char ch = getch(); 
        if (ch == '\r') { 
            break; 
        } else if (ch == 8) { 
            if (i > 0) {
                i--; 
                printf("\b \b"); 
            }
        } else if (i < MAX_SENHA - 1) { 
            senha[i] = ch; 
            printf("*"); 
            i++; 
        }
    }
    senha[i] = '\0'; 
    printf("\n");
    return senha; 
}

// Função para capturar uma opção válida (1, 2 ou 3)
int CapturarOpcao() {
    int opcao = 0;
    while (1) {
        char ch = getch(); 
        if (ch >= '1' && ch <= '3') { // Aceita apenas '1', '2' ou '3'
            opcao = ch - '0'; // Converte o caractere para número
            printf("%c\n", ch); // Exibe o número selecionado
            break;
        }
    }
    return opcao;
}

int main() {

    setlocale(LC_ALL, "Portuguese_Brazil.1252");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // manipulador do console
    COORD cursorPos; // armazenar a posição do cursor

    FILE *fpIN;
    int option = 0;
    char user[MAX_LOGIN];
    char *senha, *confirmaSenha;

    do {
        printf("==========================================\n");
        printf("                    TIN\n");
        printf("              SEJA BEM - VINDO \n");
        printf("==========================================\n");
        printf("\n1 - Login\n2 - Cadastrar\n3 - Sair\n");
        printf("\n> Escolha uma opção: ");

        // Salvar a posição atual do cursor
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        cursorPos = csbi.dwCursorPosition;

        // Adiciona a frase extra abaixo
        printf("\n\n\n@TIN - Tecnologia Implementada aos Negocios");

        // Retorna o cursor para a posição da entrada
        SetConsoleCursorPosition(hConsole, cursorPos);

        // Captura apenas uma opção válida
        option = CapturarOpcao();
        system("cls");

        switch(option) {
            case 1:
                printf("==========================================\n");
                printf("                    TIN\n");
                printf("               ÁREA DE LOGIN \n");
                printf("==========================================\n");
                printf("\nUsuário: ");
                fgets(user, MAX_LOGIN, stdin);
                user[strcspn(user, "\n")] = 0; 

                senha = CriaSenha(); 

                fpIN = fopen("usuarios.txt", "r");
                if (fpIN == NULL) {
                    printf("Erro ao abrir o arquivo.\n");
                    free(senha);
                    continue;
                }

                if (Usuario(fpIN, user, senha)) {
                    strcpy(usuarioAtual, user);

                    printf("\n-- Acesso confirmado --\n");
                    Sleep(1500);
                    system("cls");
                    menusistema(); // Chama a tela MenuSistema.c após login bem-sucedido
                    break;

                } else {
                    printf("\n=========================================\n");
                    printf("        USUÁRIO OU SENHA INCORRETOS\n");
                    printf("             TENTE NOVAMENTE\n");
                    printf("=========================================\n");
                    Sleep(2000);
                    system("cls");
                }

                fclose(fpIN);
                free(senha); 
                break;

            case 2:
                printf("Usuário: "); 
                fgets(user, MAX_LOGIN, stdin);
                user[strcspn(user, "\n")] = 0; 

                do {
                    senha = CriaSenha(); 
                    printf("Confirmação de senha: ");
                    confirmaSenha = CriaSenha();

                    if (strcmp(senha, confirmaSenha) == 0) {
                        fpIN = fopen("usuarios.txt", "a");
                        if (fpIN == NULL) {
                            printf("Erro ao abrir o arquivo.\n");
                            free(senha);
                            free(confirmaSenha);
                            continue;
                        }

                        fprintf(fpIN, "%s %s\n", user, senha); 
                        fclose(fpIN);

                        printf("Registro efetuado com sucesso!\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    } else {
                        printf("As senhas não coincidem.\n Tente novamente.\n");
                        Sleep(2000);
                        system("cls");
                    }

                    free(senha); 
                    free(confirmaSenha); 
                } while (1);

                break;

            case 3:
                return 0; 

            default:
                printf("Escolha 1, 2 ou 3...\n");
                break;
        }
    } while (1);
    return 0;
}
