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

    /*-------------------------Consideraciones---------------------------------*/
    /*
    # Si hay un error de alocación retorna NULL.
    */

    // Construcción del grafo
    Grafo g = ConstruccionDelGrafo();
    if(g!=NULL){
        printf("== fun Numero Vertices: %lu ==\n", g->nver);
        printf("== fun Numero Lados: %lu ==\n", g->mlados);
        printf("== fun Delta: %lu ==\n", g->delta);
    }
    else{
        printf("\n No se pudo construir el grafo. \n");
        return 0;
    }

    // Coloreo con Greedy
    u32 * orden = malloc(g->nver * sizeof(u32));
        for(u32 i = 0; i < g->nver; i++){orden[i] = i;}
    u32 * coloreo = malloc(g->nver * sizeof(u32));
    u32 nColores = 0;
    nColores = Greedy(g, orden, coloreo);
    printf("nColores: %lu\n", nColores);


    /*------------------------- ALEATORIZAR KEYS -------------------------------*/ 

    /* TEST de ALEATORIZAR KEYS */

    /* CASOS DE PRUEBA 01 */
    // Caso basico - Aleatorizar keys
    u32 * key = malloc(g->nver * sizeof(u32));
    for(u32 i = 0; i < g->nver; i++){
        key[i] = rand() % g->nver;
    }

    // Copia de Key
    u32 * keyCopia = malloc(g->nver * sizeof(u32));
    for(u32 i = 0; i < g->nver; i++){
        keyCopia[i] = key[i];
    }

    u32 R = rand() % g->nver;
    AleatorizarKeys(g->nver,R,key);
    // Verificamos que exista al menos una diferencia entre el key original y el aleatorizado
    u32 i = rand()%g->nver;

    while(i < g->nver){
        if(keyCopia[i] != key[i]){
            printf("OK: AleatorizarKeys - Caso básico\n");
            printf("keyOriginal[%lu]:%lu; keyModificada[%lu]:%lu \n", i,keyCopia[i],i,key[i]);
            break;
        }
        else{
            printf("FALLO: AleatorizarKeys - no hay cambios entre el keys modificado y el original\n");
            printf("keyOriginal[%lu]:%lu; keyModificada[%lu]:%lu \n", i,keyCopia[i],i,key[i]);
            break;
        }
    }

    printf("Caso Básico: Keys\n");
    for(u32 i=0; i<g->nver; i++){
        printf("key[%lu]: %lu \n",i,key[i]);
    }
    free(keyCopia);
    keyCopia = NULL;


    /* CASOS DE PRUEBA 02 */
    // Velocidad x1000 Aleatorizar keys
    clock_t talea_init, talea_end;
    double duration;
    talea_init = clock();
    for (u32 i = 0; i < 1000; i++){
        AleatorizarKeys(g->nver,i,key);
    }
    talea_end = clock();
    duration = (double)(talea_end - talea_init ) / CLOCKS_PER_SEC;
    printf("== fun Tiempo x1000 RecoloreoCardinalidadDecrecienteBC: %f ==\n", duration);
    printf("== fun Tiempo x1000 RecoloreoCardinalidadDecrecienteBC: %d horas, %d minutos, %d segundos ==\n", 
        (int)(duration)/3600, 
        ((int)(duration)%3600)/60, 
        (int)(duration)%60);

    /* FIN TEST */
    

    /*--------------------------------------------------------*/ 


    // Liberamos los arrays usados
    free(orden);
    orden = NULL;

    free(coloreo);
    coloreo = NULL;

    free(keyCopia);
    keyCopia = NULL;

    free(key);
    key = NULL;

    DestruccionDelGrafo(g);
    g = NULL;

    return 0;
}
