#include <stdio.h>
#include <stdlib.h>

#define typeof(var) _Generic( (var),\
char: "Char",\
int: "Integer",\
float: "Float",\
char *: "String",\
void *: "Pointer",\
default: "Undefined")

#define size_str 200

// define: definir constantes para strings

void Menu();

void criarTabela();

void listarTabelas();

void criarLinha();

void listarDados();

void pesquisarValor();

void apagarValor();

void apagarTabela();
