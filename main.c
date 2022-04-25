#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "AlduinPaarthurnaxIrileth.h"
#include "EstructuraGrafo.h"

int main(){
    printf("Proyecto GRAFO iniciado");
    Grafo g = ConstruccionDelGrafo();
    if(g!=NULL){
        printf("== fun Numero Vertices: %lu ==\n", g->nver);
        printf("== fun Numero Lados: %lu ==\n", g->mlados);
        printf("== fun Delta: %lu ==\n", g->delta);

        /*--------------------------------------------------------*/ 
        // crear arreglo orden e inicializar con los indices de los vertices
        u32 * orden = malloc(g->nver * sizeof(u32));
        for(u32 i = 0; i < g->nver; i++){orden[i] = i;}
        u32 * coloreo = malloc(g->nver * sizeof(u32));
        // llamar a greedy
        u32 nColores = Greedy(g, orden, coloreo);
        printf("== fun Greedy: %lu ==\n", nColores);

        //printear vertice con su color asignado
        for(u32 i = 0; i < g->nver; i++){
            printf("== fun Vertice %lu con color %lu ==\n", Nombre(i,g), coloreo[i]);
        }


        //liberar los arreglos de orden y coloreo
        free(orden);
        free(coloreo);
        /*--------------------------------------------------------*/ 
        
        DestruccionDelGrafo(g);
        return 0;
        
    }
    else{
        printf("\n No se pudo construir el grafo. \n");
        return 0;
    }
    
}
