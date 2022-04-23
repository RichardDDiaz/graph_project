#ifndef _ESTRUCTURAGRAFO_H
#define _ESTRUCTURAGRAFO_H
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long int u32;


struct _VerticeSt
{
	u32 nombrev; // nombre del vertice
	u32 gradov; // grado del vertice
	u32 positionOrdNat; // posicion natural del vertice si esta ordenado
  struct _VerticeSt ** vecinos; //arreglo de punteros de los vecinos
};

typedef struct _VerticeSt * Vertice;

/* vertice: apunta a un vertice, este puntero sera el que se tiene que 
 *		intercambiar cuando quieras ordenar con alguna de las funciones
 *		de ordenamiento a implementar
 * ordNatVertice: apunta a un vertice cual es el que deberia estar en
 * 		 esta posicion si se lo busca por orden natural.
 *       Cuando intercambies dos vertices (osea el puntero vertice),
 * 		 deberas fijarte en mantener a el puntero de ordNatVertice que 
 * 		 siga apuntando al vertice correspondiente.
*/

/*
struct _PosVerticeSt
{
	Vertice vertice;
	Vertice ordNatVertice;
};
*/

//typedef struct _PosVerticeSt * PosVertice;


typedef struct _GrafoSt
{
	u32 nver; // cantidad de vertices
	u32 mlados; // cantidad de lados
	u32 delta; // grado maximo del grafo

	Vertice * vertices;

} GrafoSt;

#endif //_ESTRUCTURAGRAFO_H