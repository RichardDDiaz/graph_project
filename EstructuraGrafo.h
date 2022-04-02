#ifndef _ESTRUCTURAGRAFO_H
#define _ESTRUCTURAGRAFO_H
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long int u32;

struct _VerticeSt
{
	u32 nombrev; // nombre del vertice
	u32 colorv; // color del vertice
	u32 gradov; // grado del vertice
  struct _VerticeSt ** vecinos; //arreglo de punteros de los vecinos
};

typedef struct _VerticeSt * Vertice;

/*
Por que teniamos aristas?
struct _AristaSt
{
	Vertice  extremo1;
	Vertice  extremo2;
};

typedef struct _AristaSt * Arista;
*/

typedef struct _GrafoSt
{
	u32 nver; // cantidad de vertices
	u32 mlados; // cantidad de lados
	u32 ccolor; // cantidad de colores
	u32 delta; // grado maximo del grafo

	Vertice * vertices; // Arreglo de punteros de VerticeSt
	Vertice * vertOrdNat; // Arreglo de punteros de VerticeSt Orden Natural

	//Arista * aristaArr; // Arreglo con punteros a estructuras AristaSt
} GrafoSt;

#endif //_ESTRUCTURAGRAFO_H