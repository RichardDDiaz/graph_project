#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "helpers.h"

u32 greedy_check(Grafo g, u32 * Coloreo, u32 nColores){
    //recorrer cada vertice del grafo g
    u32 posicionJvecinodeK = 0;
    for (u32 k=0; k < g->nver; k++){
        for (u32 j=0; j < g->vertices[k]->gradov; j++){
            posicionJvecinodeK = IndiceONVecino(j, k, g);
            if (Coloreo[k] == Coloreo[posicionJvecinodeK]){
                printf("ERROR-VERTICE Y VECINO CON EL MISMO COLOR\n");
                printf("Vertice %lu, PostNat: %lu, color: %lu\n",
                    g->vertices[k]->nombrev, k, Coloreo[k]);
                printf("Vecino %lu, PostNat: %lu, color: %lu\n",
                    g->vertices[posicionJvecinodeK]->nombrev, 
                    posicionJvecinodeK, Coloreo[posicionJvecinodeK]);
                return 0;
            }
            else if (Coloreo[posicionJvecinodeK] == -1lu){
                printf("ERROR-VERTICE CON COLOR -1\n");
                printf("Vertice %lu, PostNat: %lu, color: %lu\n",
                    g->vertices[k]->nombrev, k, Coloreo[k]);
                return 0;
            }
            else if (Coloreo[posicionJvecinodeK] >= nColores){
                printf("ERROR-VERTICE CON COLOR MAYOR AL NUMERO DE COLORES\n");
                printf("Esto no Puede ser \n");
                printf("Vertice %lu, PostNat: %lu, color: %lu\n",
                    g->vertices[k]->nombrev, k, Coloreo[k]);
                return 0;
            }
        }
    }
    return 1;
}


// reviso uno a uno que los colores respeten la biyección de PermutarColores
// return 1 si la permutación de colores es correcta.
// return 0 si hubo algun error en la permutación
u32 permutarColores_cheeck(u32 * Coloreo, u32 * NuevoColoreo, u32 n){
    // coloresPermutados representara la biyección: la posición del array 
    // representara el color en Coloreo y el valor de la posición el color permutado
    u32 * coloresPermutados = malloc(sizeof(u32)*1);
    coloresPermutados[0] = 0;
    u32 colorNuevo = 0;
    // itero Coloreo, obtengo el maximo color
    printf("Permutar CHECK\n");
    for(u32 i=0;i<n; i++){
        // agregamos nuevo color
        printf("Permutar for\n");
        printf("Colreo[%lu]= %lu", i,Coloreo[i]);
        if(colorNuevo < Coloreo[i]){
            printf("Permutar for - if\n");
            colorNuevo = Coloreo[i];
            coloresPermutados = realloc(coloresPermutados, sizeof(u32)*(colorNuevo+1));
        }
        coloresPermutados[Coloreo[i]] = NuevoColoreo[i];
    }

    // verificamos los colores iterando en Coloreo
    printf("Permutar CHECK 2\n");
    u32 i = 0;
    while(i < n){
        printf("Permutar While\n");
        if(NuevoColoreo[i] != coloresPermutados[Coloreo[i]]){
            printf("Permutar Colores: NO TIENEN EL MISMO VALOR POSICIÓN %lu, NuevoColoreo=%lu , Coloreo=%lu \n", i,NuevoColoreo[i],Coloreo[i]);
            i = n+1;
        }
        i++;
    }
    printf("Permutar CHECK 3\n");
    if(i > n){
        printf("Permutar i > n\n");
        printf("Permutar Colores: NO TIENEN EL MISMO VALOR POSICIÓN %lu, NuevoColoreo=%lu , Coloreo=%lu \n", i,NuevoColoreo[i],Coloreo[i]);
        return 0;
    }
    free(coloresPermutados);
    coloresPermutados = NULL;

    printf("Permutar colores exitoso\n");
    return 1;
}