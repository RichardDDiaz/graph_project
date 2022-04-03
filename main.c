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

void main(){
    printf("Proyecto GRAFO iniciado");
    Grafo g = ConstruccionDelGrafo();
    assert(g != NULL && "Grafo es Null");
    printf("\n Construccion del grafo: Finalizada \n");
    
    printf("vertices: \n");
    for(u32 i = 0; i < g->nver; i++){
        printf("%lu: ", g->vertices[i]->nombrev);
       /* for(u32 j=0; j < g->vertices[i]->gradov; j++){
            printf("%lu-", g->vertices[i]->vecinos[j]->nombrev);
        }*/
        
        printf("\n");
    }
    printf("delta: %lu \n",g->delta);
}