#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

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
    //u32 n = 10u;
    //u32 * key = malloc(sizeof(int)*10);
    //for(u32 i=0; i<n;i++){
        //key[i] = 0;
    //}
    //u32 R = 10u;
    //AleatorizarKeys(n,R,key);
    //free(key);
    /*--------------------------------------------------------*/ 

    Grafo g = ConstruccionDelGrafo();
    if(g!=NULL){
        printf("== fun Numero Vertices: %lu ==\n", g->nver);
        printf("== fun Numero Lados: %lu ==\n", g->mlados);
        printf("== fun Delta: %lu ==\n", g->delta);

        // imprimir vecinos del vertice 1 en el orden natural
        printf("== vecinos del vertice 0 en el orden natural ==\n");
        for (u32 i = 0; i < Grado(0, g); i++) {
            printf("%lu\n", g->vertices[0]->vecinos[i]->nombrev);
        }
        printf("== fin vecinos del vertice 1 en el orden natural ==\n");

        printf("== vecinos del vertice 1 en el orden natural ==\n");
        for (u32 i = 0; i < Grado(1, g); i++) {
            printf("%lu\n", g->vertices[1]->vecinos[i]->nombrev);
        }
        printf("== fin vecinos del vertice 1 en el orden natural ==\n");
        /*------------------------- BIPARTITO -------------------------------*/ 
        
        u32 * coloreo = NULL;

        coloreo = Bipartito(g);
        if(coloreo!=NULL){
            printf("== fun Coloreo: ");
            for(u32 i=0; i<g->nver; i++){
                printf("%lu ", coloreo[i]);
            }
            printf("==\n");
            free(coloreo);
        }else{
            printf("== fun Coloreo: NULL ==\n");
        }
        

        /*-------------------------------------------------------------------*/ 



        /*------------------------- GREEDY -------------------------------*/ 
        /*
        clock_t tgreedy_init, tgreedy_end;
        double duration;
        // crear arreglo orden e inicializar con los indices de los vertices
        u32 * orden = malloc(g->nver * sizeof(u32));
        for(u32 i = 0; i < g->nver; i++){orden[i] = i;}
        // Arreglo de colores
        u32 * coloreo = malloc(g->nver * sizeof(u32));
        // llamar a greedy
        u32 nColores = 0;
        tgreedy_init = clock();
        for (u32 i = 0; i < 1000; i++){
            nColores = Greedy(g, orden, coloreo);
        }

        tgreedy_end = clock();
        printf("== fun Greedy: %lu ==\n", nColores);

        duration = (double)(tgreedy_end - tgreedy_init ) / CLOCKS_PER_SEC;
        printf("== fun Tiempo Greedy: %f ==\n", duration);
        printf("== fun Tiempo Greedy: %d horas, %d minutos, %d segundos ==\n", 
            (int)(duration)/3600, 
            ((int)(duration)%3600)/60, 
            (int)(duration)%60);
    

        // Verificar el coloreo de greedy sea propio
        //if(greedy_check(g, coloreo, nColores)){
            if(true){
            printf("== fun Greedy: OK ==\n");
        }
        else{
            printf("== fun Greedy: ERROR ==\n");
        }

        //liberar los arreglos de orden y coloreo
        free(orden);
        orden = NULL;
        free(coloreo);
        coloreo = NULL;
        */
        /*--------------------------------------------------------*/

        /*-----------------OrdenFromKey---------------------------*/
        /*
        u32 n = 10000;
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
        
        // chequear que el orden sea correcto
        if(ordenfromkey_check(n, key_arreglo, orden_arreglo)){
            printf("== fun OrdenFromKey: OK ==\n");
        }
        else{
            printf("== fun OrdenFromKey: ERROR ==\n");
        }
        
        // liberar los arreglos
        free(key_arreglo);
        free(orden_arreglo);
        key_arreglo = NULL;
        orden_arreglo = NULL;
        */
        /*--------------------------------------------------------*/


        
        DestruccionDelGrafo(g);
        return 0;
        
    }
    else{
        printf("\n No se pudo construir el grafo. \n");
        return 0;
    }
    
}
