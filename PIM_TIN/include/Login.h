#ifndef LOGIN_H
#define LOGIN_H
#include <stdio.h>

extern char usuarioAtual[100]; // Definir variável global para usuario logado

int Usuario(FILE *file, char *user, char *senha);
char* CriaSenha();

#endif // LOGIN_H
