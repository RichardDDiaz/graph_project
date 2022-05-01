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
    Grafo g = ConstruccionDelGrafo();
    if(g!=NULL){
        printf("== fun Numero Vertices: %lu ==\n", g->nver);
        printf("== fun Numero Lados: %lu ==\n", g->mlados);
        printf("== fun Delta: %lu ==\n", g->delta);
        /*------------------------- GREEDY -------------------------------*/ 
        /*
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
            printf("== fun Greedy: OK ==\n");
        }
        else{
            printf("== fun Greedy: ERROR ==\n");
        }

        //liberar los arreglos de orden y coloreo
        free(orden);
        free(coloreo);
        */
        /*--------------------------------------------------------*/

        /*-----------------OrdenFromKey---------------------------*/
        u32 n = 20;
        // crear un arreglo de longitud 20 con numeros aleatorios
        // entre 0 y 20
        u32 * key_arreglo = malloc(n * sizeof(u32));
        for(u32 i = 0; i < n; i++){
            key_arreglo[i] = rand() % n;
        }
        printf("== ARREGLO KEY\n:");
        for(u32 i = 0; i < n; i++){
            printf("%lu ", key_arreglo[i]);
        }
        printf("\n");

        u32 * orden_arreglo = malloc(n * sizeof(u32));

        // llamar a ordenFromKey
        char rorden = OrdenFromKey(n, key_arreglo, orden_arreglo);

        if (rorden == '1'){
            printf("== fun OrdenFromKey: ERROR, falta memoria ==\n");
        }
        else{
            printf("== fun OrdenFromKey: OK, se ejecuto bien ==\n");
        }

        printf("== ARREGLO ORDEN: ");
        for(u32 i = 0; i < n; i++){
            printf("%lu ", orden_arreglo[i]);
        }
        printf("\n FINALIZADO\n");

        for (u32 i = 0; i < n; i++){
            printf("%lu, ", key_arreglo[orden_arreglo[i]]);
        }
        printf("\n");

        DestruccionDelGrafo(g);
        return 0;
        
    }
    else{
        printf("\n No se pudo construir el grafo. \n");
        return 0;
    }
    
}
