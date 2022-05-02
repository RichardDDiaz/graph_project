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
#include "helpers.h"

int main(){
    printf("Proyecto GRAFO iniciado");
    
    /*------------------------- ALEATORIZAR KEYS -------------------------------*/ 
    /*
    Nota: Retorna numeros aleatorios, requiere mejorar la función ya que solo retorna 
    numeros "pseudo-aleatorios" que forman parte de una misma secuencia. 
    Es decir: Si con R generamos los [0,n] numeros aleatorios, con R+1 generara 
    los [1,n+1] numeros siguientes de la secuencia.
    */
    u32 n = 10u;
    u32 * key = malloc(sizeof(int)*10);
    for(u32 i=0; i<n;i++){
        //key[i] = 0;
    }
    u32 R = 10u;
    AleatorizarKeys(n,R,key);
    free(key);
    /*--------------------------------------------------------*/ 

    Grafo g = ConstruccionDelGrafo();
    if(g!=NULL){
        printf("== fun Numero Vertices: %lu ==\n", g->nver);
        printf("== fun Numero Lados: %lu ==\n", g->mlados);
        printf("== fun Delta: %lu ==\n", g->delta);
        /*------------------------- GREEDY -------------------------------*/ 
        // crear arreglo orden e inicializar con los indices de los vertices
        u32 * orden = malloc(g->nver * sizeof(u32));
        for(u32 i = 0; i < g->nver; i++){orden[i] = i;}
        // Arreglo de colores
        u32 * coloreo = malloc(g->nver * sizeof(u32));
        // llamar a greedy
        u32 nColores = Greedy(g, orden, coloreo);
        printf("== fun Greedy: %lu ==\n", nColores);

        // Verificar el coloreo de greedy sea propio
        if(greedy_check(g, coloreo, nColores)){
            if(true){
            printf("== fun Greedy: OK ==\n");
        }
        else{
            printf("== fun Greedy: ERROR ==\n");
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
