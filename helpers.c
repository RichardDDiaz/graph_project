#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "helpers.h"
#define ErrorGrafo 4294967295

void enqueue(Queue *queue, Queue  *lastElem, u32 value){
    Queue newElem = malloc(sizeof(struct _Queue));
    if (newElem == NULL){
        return;
    }
    newElem->value = value;
    newElem->next = NULL;
    newElem->prev = NULL;
    if (*queue == NULL){
        *queue = newElem;
        *lastElem = newElem;
    }
    else {
        (*queue)->prev = newElem;
        newElem->next = *queue;
        *queue = newElem;
    }
    newElem = NULL;
}


u32 dequeue(Queue *queue, Queue *lastElem){
    if (*queue == NULL){
        return ErrorGrafo;
    }
    // extraemos el value de lastElem
    u32 item = (*lastElem)->value;
    // eliminamos lastElem de la lista

    //si es el unico elemento
    if ((*lastElem)->prev == NULL && (*lastElem)->next == NULL){
        *queue = NULL;
        free(*lastElem);
        *lastElem = NULL;
    }
    else{
        Queue prev = (*lastElem)->prev;
        prev->next = NULL;
        (*lastElem)->prev = NULL;
        free(*lastElem);
        *lastElem = prev;
        prev = NULL;
    }

    return item;
}


void freeQueue(Queue *queue){
    if (*queue == NULL){
        return;
    }
    Queue node = *queue;
    Queue next_node = NULL;
    while (node != NULL){
        next_node = node->next;
        free(node);
        node = next_node;
    }
    *queue = NULL;
    node = NULL;
    next_node = NULL;
}

u32 coloreoBipartitoConexo(Grafo G, u32 *Coloreo, u32 index){
    if (G == NULL || Coloreo == NULL || Coloreo[index] != ErrorGrafo){ 
        return ErrorGrafo;
    }

    //Coloreamos el vertice i index
    Coloreo[index] = 1lu;
    //Encolar el index vertice i en la cola
    Queue queue = NULL;
    Queue lastElem = NULL;
    enqueue(&queue, &lastElem, index);

    if (queue == NULL){
        //free(Coloreo);
        //Coloreo = NULL;
        return ErrorGrafo;
    }
    while(queue != NULL){
        //sacamos el primer elemento (indice) de la cola
        index = dequeue(&queue, &lastElem);
        //para cada vecino de indice
        for (u32 i=0; i < Grado(index, G); i++){
            //si el vecino no esta coloreado
            if (Coloreo[IndiceONVecino(i, index, G)] == ErrorGrafo){
                //coloreamos el vecino con el opuesto del coloreo de indice
                Coloreo[IndiceONVecino(i, index, G)] = Coloreo[index] == 1lu ? 2lu : 1lu;
                //encolamos el indice del vecino
                enqueue(&queue, &lastElem, IndiceONVecino(i, index, G));
            }
            else {
                //si el vecino esta coloreado
                //si el coloreo de indice es igual al coloreo de vecino
                if (Coloreo[index] == Coloreo[IndiceONVecino(i, index, G)]){
                    //no es bipartito
                    //DESTRUIR EL ARREGLO COLOREO Y LA COLA QUE CONTIENE LOS INDICES
                    //free(Coloreo);
                    freeQueue(&queue);
                    //Coloreo = NULL;
                    queue = NULL;
                    lastElem = NULL;
                    return ErrorGrafo;
                }
            }
        }
    }
    if (queue != NULL){
        freeQueue(&queue);
        queue = NULL;
        lastElem = NULL;
    }
    return 1lu;
}


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


int bipartito_check(Grafo g, u32 * Coloreo){
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
            else if (Coloreo[k] != 1 && Coloreo[k] != 2){
                printf("ERROR-VERTICE CON COLOR NO BIPARTITO\n");
                printf("Vertice %lu, PostNat: %lu, color: %lu\n",
                    g->vertices[k]->nombrev, k, Coloreo[k]);
                return 0;
            }
            else if (Coloreo[posicionJvecinodeK] != 1 && Coloreo[posicionJvecinodeK] != 2){
                printf("ERROR-VERTICE vecino CON COLOR NO BIPARTITO\n");
                printf("Vertice vecino %lu, PostNat: %lu, color: %lu\n",
                    g->vertices[posicionJvecinodeK]->nombrev,
                    posicionJvecinodeK, Coloreo[posicionJvecinodeK]);
                return 0;
            }
            else{
                return 1;
            }
        }
    }
    return 0;
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
