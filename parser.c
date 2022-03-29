#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "parser.h"

void run_parser(Grafo g){
    char path_name[100];
    printf("Indique ruta del archivo: \n");
    int scan_path_name = scanf("%s", path_name);
    assert(scan_path_name > 0 && "Error al leer ruta del archivo");

    FILE *file = fopen(path_name, "r");
    assert(file != NULL && "Error al abrir archivo");
    printf("Archivo Abierto\n");

    char first_char;
    
    // Empezar a leerlo como especificamos en el documento
}