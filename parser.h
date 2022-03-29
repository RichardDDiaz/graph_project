#ifndef _PARSER_H
#define _PARSER_H
#include <stdbool.h>
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"


// funcion hash
int hash(char *str);

// cambiar los tipos de datos pero buscar el vertice  y retornar
// el vertice o null
bool buscar_vertice(int v, int *vertices);

// poner el vertice1 como vecino del vertice2 y viceversa
void emparejar_vertices(int vOne, int vTwo);

// cambiar los tipos de datos de entrada y salida 
// construccion del grafo
void run_parser(int grafo)

#endif //_PARSER_H