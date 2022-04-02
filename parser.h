#ifndef _PARSER_H
#define _PARSER_H
#include <stdbool.h>
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"


// funcion hash
int hash(char *str);

// funcion que busca el vertice en el grafo y si no existe lo crea
// finalmente retornando un puntero al vertice.
Vertice buscar_vertice(Grafo g, u32 nombreVertice);

// poner el vertice1 como vecino del vertice2 y viceversa
void emparejar_vertices(int vOne, int vTwo);

// cambiar los tipos de datos de entrada y salida 
// construccion del grafo
void run_parser(Grafo grafo);

#endif //_PARSER_H