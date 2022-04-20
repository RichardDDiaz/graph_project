#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "EstructuraGrafo.h"
//#include "parser.h"

int main(){
    printf("Proyecto GRAFO iniciado");
    Grafo g = ConstruccionDelGrafo();
    if(g!=NULL){
        //printf("== fun Numero Vertices: %lu ==\n", NumeroDeVertices(g));
        //printf("== fun Numero Lados: %lu ==\n", NumeroDeLados(g));
        //printf("== fun Delta: %lu ==\n", Delta(g));

        printf("== fun Numero Vertices: %lu ==\n", g->nver);
        printf("== fun Numero Lados: %lu ==\n", g->mlados);
        printf("== fun Delta: %lu ==\n", g->delta);


        //recorrer todos los vertices en un for
        for(u32 i=0; i<g->nver; i++){
            //printf(" %p == %p \n", g->vertices[i]->ordNatVertice, g->vertices[i]->vertice);
            //printf("== Vertice: %lu ==\n", g->vertices[i]->ordNatVertice->nombrev);
            printf("== V: %lu, OrdV: %lu ==\n", g->vertices[i]->vertice->nombrev, g->vertices[i]->ordNatVertice->nombrev);
        }
            
        printf("indice k: %lu, vertice: %lu\n",4lu, Nombre(4,g));
        printf("vecinoIndice j: %lu, vecino: %lu\n", 0lu, IndiceONVecino(0,4,g));
        printf("vecinoIndice j: %lu, vecino: %lu\n", 1lu, IndiceONVecino(1,4,g));
        printf("vecinoIndice j: %lu, vecino: %lu\n", 2lu, IndiceONVecino(2,4,g));


        DestruccionDelGrafo(g);
        return 0;
        
    }
    else{
        printf("\n No se pudo construir el grafo. \n");
        return 0;
    }
    
}
