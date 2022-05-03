#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "helpers.h"


int compararTuplas(const void * a, const void * b){
    Tuple t1 = *((Tuple*)a);
    Tuple t2 = *((Tuple*)b);
    
    if(t1->v1 > t2->v1){
        return -1;
    }
    else if(t1->v1 < t2->v1){
        return 1;
    }
    else{
            return 0;
    }
}


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


/* Es decir, da un orden de los indices tal que Orden[i]6=Orden[j] si i 6= j y tal que:
key[Orden[0]] ≥ key[Orden[1]] ≥ key[Orden[2]] ≥ .... ≥ key[Orden[n-1]]
*/
int ordenfromkey_check(u32 n,u32* key,u32* Orden){
    for (u32 i=0; i < n; i++){
        for (u32 j=i+1; j < n; j++){
                if (key[Orden[i]] < key[Orden[j]]){
                    printf("ERROR-ORDEN INCORRECTO\n");
                    printf("key[Orden[%lu]] = %lu, es mayor igual que\n", i, key[Orden[i]]);
                    printf("key[Orden[%lu]] = %lu\n", j, key[Orden[j]]);

                    return 0;
                }
        }
    }
    return 1;
}