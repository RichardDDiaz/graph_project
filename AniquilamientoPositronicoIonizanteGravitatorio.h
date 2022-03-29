#ifndef __APIG_H
#define __APIG_H


#include <stdio.h>
#include <stdlib.h>


//Funciones referidas a la estructura del GRAFO solamente (vertices y lados, basicamente)
//y no a sus colores o el orden en que se correra Greedy.
//es decir, solo referidas a la ESTRUCTURA del grafo.
//todos estos datos son fijos una vez cargado el grafo.

#include "EstructuraGrafo.h"

//Grafo es un puntero a una estructura, la cual esta definida en el .h de arriba

typedef GrafoSt *Grafo;


//construcci'on/destrucci'on del grafo

Grafo ConstruccionDelGrafo();

void DestruccionDelGrafo(Grafo G);


//funciones para extraer datos del grafo. u32 esta definida en el .h de arriba

u32 NumeroDeVertices(Grafo G);
u32 NumeroDeLados(Grafo G);
u32 Delta(Grafo G);


//funciones de infoextract de vertices 
//valor de retorno (2 a la 32)-1 para reportar errores.
// "Nombre" no tienen forma de reportar errores.
//las otras no hay problema pues es imposible que (2 a la 32)-1 sea un indice o un grado.
//el indice i es el indice en el orden natural
u32 Nombre(u32 i,Grafo G);
u32 Grado(u32 i,Grafo G);
//vecinos info
u32 IndiceONVecino(u32 j,u32 k,Grafo G);



#endif
