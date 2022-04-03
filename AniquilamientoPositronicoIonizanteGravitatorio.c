#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "parser.h"

#define ErrorGrafo 4294967295 

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

/*
void DestruccionDelGrafo(Grafo G){
	free(G->vertices);
	G->vertices = NULL;

	free(G->vertOrdNat);
	G->vertOrdNat = NULL;

	free(G);
	G = NULL;
}
*/

void DestruccionDelGrafo(Grafo G){
	// vaciar los arreglos de punteros de cada vecino de cada vertice
	for(u32 j=0 ; j < G->nver; j++){
		for(u32 k=0 ; k<G->vertices[j]->gradov; k++){
      		G->vertices[j]->vecinos[k] = NULL;
    	}
    	free(G->vertices[j]->vecinos);
		G->vertices[j]->vecinos = NULL;
	}
	// eliminar cada vertice del arreglo de punteros de vertices
	for(u32 l=0 ; l<G->nver; l++){
		
		free(G->vertices[l]);
		G->vertices[l] = NULL;
	}
	free(G->vertices);
  	G->vertices = NULL;
  	free(G);
  	G = NULL;
}


u32 NumeroDeVertices(Grafo G){
  return G->nver;
}


u32 NumeroDeLados(Grafo G){
  return G->mlados;
}


u32 Delta(Grafo G){
  return G->delta;
}

u32 Nombre(u32 i,Grafo G){
  return G->vertOrdNat[i]->nombrev;
}


u32 Grado(u32 i,Grafo G){
	if (i >= G->nver){
  		return ErrorGrafo;
  	}
  	else{
  		return G->vertOrdNat[i]->gradov;
  	}
}

u32 IndiceONVecino(u32 j,u32 k,Grafo G){
	if (k < NumeroDeVertices(G) && G->vertOrdNat[k]->gradov > j &&
		G->vertOrdNat[k]->vecinos[j]->nombrev == G->vertOrdNat[j]->nombrev){
			return j;
	}
	return ErrorGrafo;
}
