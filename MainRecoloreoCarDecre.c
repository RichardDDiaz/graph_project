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

    clock_t trecade_init, trecade_end;
    double duration;

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


    /* TEST de RecoloreoCardinalidadDecrecienteBC */

    /* CASOS DE PRUEBA 01 */
    // Caso basico - recoloreo de un grafo
    u32 * RCD_array =RecoloreoCardinalidadDecrecienteBC(g->nver,coloreo);
    if(RCD_array == NULL){
        printf("FALLO - Caso básico - Error de alocación");
        return 0;
    }
    // chequeo de coloreo
    u32 RCDCheck = RecoloreoCardinalidadDecrecienteBC_check(g->nver, coloreo, RCD_array);
    if(RCDCheck != 1){
        printf("ERROR: RecoloreoCardinalidadDecrecienteBC - Coloreo basico \n");
        return 0;
    }
    free(RCD_array);
    RCD_array = NULL;

    /* CASOS DE PRUEBA 02 */
    // Velocidad de Recoloreo y Greedy
    trecade_init = clock();
    for (u32 i = 0; i < 1000; i++){
        //nColores = Greedy(g, orden, coloreo);
        RCD_array =RecoloreoCardinalidadDecrecienteBC(g->nver,coloreo);
        free(RCD_array);
        RCD_array = NULL;
        
    }
    trecade_end = clock();
    duration = (double)(trecade_end - trecade_init ) / CLOCKS_PER_SEC;
    printf("== fun Tiempo x1000 RecoloreoCardinalidadDecrecienteBC: %f ==\n", duration);
    printf("== fun Tiempo x1000 RecoloreoCardinalidadDecrecienteBC: %d horas, %d minutos, %d segundos ==\n", 
        (int)(duration)/3600, 
        ((int)(duration)%3600)/60, 
        (int)(duration)%60);

    /* FIN TEST */


    // Liberamos los arrays usados
    free(orden);
    orden = NULL;

    free(coloreo);
    coloreo = NULL;

    DestruccionDelGrafo(g);
    g = NULL;

    return 0;
}
