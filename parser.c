#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "parser.h"


Grafo ConstruccionDelGrafo()
{
	//creo un grafo y le reservo memoria
	Grafo g = malloc(sizeof(GrafoSt));
	//chequeo que malloc haya terminado exitosamente
    if (g == NULL) {
        printf("No hay suficiente memoria para el grafo :( )\n");
    }
	//inicializo los datos
	g->nver = 0;
	g->mlados = 0 ;
	g->ccolor = 0;
	g->delta  = 0;
	g->vertices = NULL;
    g->vertOrdNat = NULL;

	run_parser(g);
	return g;
}

void run_parser(Grafo g){
    char path_name[100];
    printf("\n Indique ruta del archivo: \n");
    int scan_path_name = scanf("%s", path_name);
    printf("filename: %s\n", path_name);

    assert(scan_path_name > 0 && "Error al leer ruta del archivo");

    FILE *file = fopen(path_name, "r");
    assert(file != NULL && "Error al abrir archivo");
    printf("Archivo Abierto\n");
    
    // leer  el primer caracter del archivo
    char firstchar;
    int count_fscanf = fscanf(file,"%c", &firstchar);
    
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
    char pseudo_edge[5]; // +1 por caracter de temrinación
    // si el primer caracter es EOF, no hay mas datos
    assert(firstchar == 'p' 
            && fscanf(file,"%s %lu %lu",pseudo_edge , &nver, &mlado) > 0
            && "Primer caracter no es 'p' o no formato (p edge n m)");
    assert(!strcmp("edge",pseudo_edge) && "no es edge, formato incorrecto");

    printf("%lu vertices y %lu Lados\n", nver, mlado);

    g->nver = nver;
    g->mlados = mlado;
    g->vertices = malloc(sizeof(Vertice) * nver);
    g->vertOrdNat = malloc(sizeof(Vertice) * nver);

    // lectura de los lados con vertices
    // formato de cada linea: e v1 v2
    u32 vA, vB;
    u32 count_m = 0;
    while(count_m <= mlado-1){
        /*
            cuando hacemos fscanf(file,"%s %lu %lu",pseudo_edge , &nver, &mlado)
            el siguiente fscanf tomara el salto de linea de la linea j-1
            y el siguiente fscanf sera el primer char de la linea j.
            no se como hacer para que lo ignore sin hacer que lo asigne a una 
            variable que no usaremos(lo probe con la var u32 vA y tampoco)
        */
        fscanf(file,"%c", &firstchar);
        u32 check_scan = fscanf(file,"%c", &firstchar);
        // estas al final de archivo o Error de lectura
        if (check_scan == EOF){
            printf("liberar memoria, retornar NULL 1\n");
            exit(EXIT_FAILURE);
        }
        // la linea cumple el formato: e v w 
        else if (firstchar == 'e' && fscanf(file,"%lu %lu", &vA, &vB) > 0){
            // ...
            // ... code here
            // ...
            printf("%lu %lu\n", vA, vB);
            count_m++;
            g->mlados++;
        }
        // la linea no lo cumple 
        else{
            printf("liberar memoria, retornar NULL 2\n");
            exit(EXIT_FAILURE);
        }
    }

    //if (g->mlados < m)
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