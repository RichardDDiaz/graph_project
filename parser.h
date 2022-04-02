#ifndef _PARSER_H
#define _PARSER_H
#include <stdbool.h>
#include "EstructuraGrafo.h"

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

// funcion hash
int hash(char *str);

// Busca/crea si no existe el vertice 
// return: puntero al vertice.
Vertice buscar_vertice(Grafo g, u32 nombreVertice);

// Establece al vertice1 como vecino del vertice2 y viceversa
void emparejarVertices(Vertice verticeA,Vertice verticeB);


// Iniciamos todos los espacios de memoria en NULL
void inicializarNullVertices(Grafo g);

// cambiar los tipos de datos de entrada y salida 
// Construccion del grafo
void run_parser(Grafo grafo);

#endif //_PARSER_H