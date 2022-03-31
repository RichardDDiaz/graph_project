#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "parser.h"

void run_parser(Grafo g){
    char path_name[100];
    printf("Indique ruta del archivo: \n");
    int scan_path_name = scanf("%s", path_name);
    printf("filename: %s\n", path_name);
    assert(scan_path_name > 0 && "Error al leer ruta del archivo");

    FILE *file = fopen(path_name, "r");
    assert(file != NULL && "Error al abrir archivo");
    printf("Archivo Abierto\n");
    
    // leer  el primer caracter del archivo
    char firstchar = fscanf(file,"%c", &firstchar);
    /* recorre los comentarios cuando el primer caracter es 'c' 
       cuando el primer caracter sea != de 'c', en teoria ya estamos
       en la parte de lectura de los lados */
    while(!feof(file) && firstchar == 'c'){
        while(firstchar != EOF && firstchar != '\n'){
            fscanf(file,"%c", &firstchar);
        }
        // te paras en el siguiente primer caracter
        fscanf(file,"%c", &firstchar);
    }

    u32 nver;
    u32 mlado;
    // si el primer caracter es EOF, no hay mas datos
    assert(firstchar != 'p' && fscanf(file,"%*s %lu %lu", &nver, &mlado) <= 0
            && "Primer caracter no es 'p' o no formato (p n m)");
    printf("%lu %lu\n", nver, mlado);
}
/*
c
c
c
c
p
e
e
e
e
*/