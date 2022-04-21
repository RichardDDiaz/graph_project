#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "EstructuraGrafo.h"

int main(){
    printf("Proyecto GRAFO iniciado");
    Grafo g = ConstruccionDelGrafo();
    if(g!=NULL){
        printf("== fun Numero Vertices: %lu ==\n", g->nver);
        printf("== fun Numero Lados: %lu ==\n", g->mlados);
        printf("== fun Delta: %lu ==\n", g->delta);


        //recorrer todos los vertices
        for(u32 i=0; i<g->nver; i++){
            printf("== nombreV: %lu, OrdV: %lu ==\n", g->vertices[i]->nombrev, i);
        }

        // Prueba: IndiceONVecino
        printf("IndiceONVecino: \n");
        printf("indice k: %lu, vertice: %lu\n",0lu, Nombre(0,g));
        for(u32 i=0; i<g->vertices[0]->gradov; i++){
            printf("vecinoIndice j: %lu, vecino: %lu\n", i, IndiceONVecino(i,0,g));
        } 

        DestruccionDelGrafo(g);
        return 0;
        
    }
    else{
        printf("\n No se pudo construir el grafo. \n");
        return 0;
    }
    
}
