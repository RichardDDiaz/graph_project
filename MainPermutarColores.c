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

    u32 * orden = malloc(g->nver * sizeof(u32));
        for(u32 i = 0; i < g->nver; i++){orden[i] = i;}
    u32 * coloreo = malloc(g->nver * sizeof(u32));
    u32 nColores = 0;
    nColores = Greedy(g, orden, coloreo);

    printf("nColores: %lu \n", nColores);
    for(u32 i=0; i<g->nver;i++){
        printf("i: %lu ; coloreo: %lu \n", i, coloreo[i]);
    }

    /*------------------------- PermutarColores -------------------------------*/
    /*
    Consideraciones:
      Si hay un error de alocación retorna NULL.
      Si Coloreo tenia Coloreo[i]=4 y ahora se cambia 4 por 7, entonces NuevoColoreo[i]=7,
        tambien para todos los i con color=4.
      Debe ser un algoritmo que demore un tiempo razonable.
    */

   /* TEST de PermutarColores */

    /* CASOS DE PRUEBA 01 */
    // Caso basico - Permutación de colores

    printf("Permutar colores:\n");
    u32 R = 10;
    u32 * NuevoColoreo = PermutarColores(g->nver ,coloreo,R);
    if(NuevoColoreo == NULL){
        printf("ERROR: Caso 1 : NuevoColoreo es NULL \n");
        return 0;
    }
    u32 result = permutarColores_cheeck(coloreo, NuevoColoreo, g->nver);
    if(result == 1){
        printf("== PermutarColores: Caso 1: OK ==\n");
    }
    else{
        printf("== PermutarColores: ERROR ==\n");
    }

    free(NuevoColoreo);
    NuevoColoreo = NULL;


    /* CASOS DE PRUEBA 02 */
    // Velocidad: 1000 Permutaciones
    clock_t tpermu_init, tpermu_end;
    double duration;
    tpermu_init = clock();
    for(u32 i=0; i<1000; i++){
        R = i;
        NuevoColoreo = PermutarColores(g->nver ,coloreo,R);
        free(NuevoColoreo);
        NuevoColoreo = NULL;
    }
    tpermu_end = clock();
    duration = (double)(tpermu_end - tpermu_init ) / CLOCKS_PER_SEC;
    printf("== fun Tiempo x1000 PermutarColores: %f ==\n", duration);
    printf("== fun Tiempo x1000 PermutarColores: %d horas, %d minutos, %d segundos ==\n", 
        (int)(duration)/3600, 
        ((int)(duration)%3600)/60, 
        (int)(duration)%60);

    /* FIN TEST */
    /*-------------------------------------------------------*/

    // Liberamos los arrays usados
    free(orden);
    orden = NULL;

    free(coloreo);
    coloreo = NULL;

    free(NuevoColoreo);
    NuevoColoreo = NULL;

    DestruccionDelGrafo(g);
    g = NULL;

    return 0;
}
