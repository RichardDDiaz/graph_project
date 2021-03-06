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
key[Orden[0]] ??? key[Orden[1]] ??? key[Orden[2]] ??? .... ??? key[Orden[n-1]]
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


// reviso uno a uno que los colores respeten la biyecci??n de PermutarColores
// return 1 si la permutaci??n de colores es correcta.
// return 0 si hubo algun error en la permutaci??n
u32 permutarColores_cheeck(u32 * Coloreo, u32 * NuevoColoreo, u32 n){
    // coloresPermutados representara la biyecci??n: la posici??n del array 
    // representara el color en Coloreo y el valor de la posici??n el color permutado
    u32 * coloresPermutados = malloc(sizeof(u32)*1);
    if(coloresPermutados == NULL){
        printf("ERROR: Fallo malloc coloresPermutados en permutarColores_cheek\n");
        return 1;
    }
    coloresPermutados[0] = 0;
    u32 colorNuevo = 0;

    // itero Coloreo, obtengo el maximo color
    for(u32 i=0;i<n; i++){
        // agregamos nuevo color
        if(colorNuevo < Coloreo[i]){
            colorNuevo = Coloreo[i];
            coloresPermutados = realloc(coloresPermutados, sizeof(u32)*(colorNuevo+1));
            if(coloresPermutados == NULL){
                printf("ERROR: fallo en realloc en PermutarColores_Check \n");
                return 1;
            }
        }
        coloresPermutados[Coloreo[i]] = NuevoColoreo[i];
    }

    // verificamos los colores iterando en Coloreo
    u32 i = 0;
    while(i < n){
        if(NuevoColoreo[i] != coloresPermutados[Coloreo[i]]){
            printf("Permutar Colores: NO TIENEN EL MISMO VALOR POSICI??N %lu, NuevoColoreo=%lu , Coloreo=%lu \n", i,NuevoColoreo[i],Coloreo[i]);
            return 0;
        }
        i++;
    }
    free(coloresPermutados);
    coloresPermutados = NULL;
    return 1;
}



// Suma la cantidad de veces que aparece cada color
Tuple * SumaRepeticionesColor(u32 n, u32 * Coloreo, u32 *cantColores){
    Tuple * nColores = malloc(sizeof(Tuple));
    if (nColores == NULL){return NULL;}
    nColores[0] = malloc(sizeof(struct _Tuple));
    if (nColores[0] == NULL){return NULL;}
    nColores[0]->v1 = 0; //cantidad del color
    nColores[0]->v2 = 0; //color

    *cantColores = 0;

    // Sumamos las veces que aparece cada color
    for(u32 i=0; i<n; i++){
        // Si encontramos un color nuevo
        if(*cantColores < Coloreo[i]){
            // agrandamos el arreglo de colores
            nColores = realloc(nColores, sizeof(Tuple)*(Coloreo[i]+1));

            // seteamos en 0 el resto de colores
            for(u32 j=(*cantColores +1); j<(Coloreo[i]+1);j++){
                nColores[j] = malloc(sizeof(struct _Tuple));
                if(nColores == NULL){return NULL;}
                nColores[j]->v1=0; // cantidad del color
                nColores[j]->v2=j; // color
            }
            *cantColores = Coloreo[i];
        }
        // Sumamos 1 al color encontrado si 
        nColores[Coloreo[i]]->v1 += 1;
    }

    // agregamos uno por la cantidad total de colores
    *cantColores +=1;
    // nColores en orden natural
    return nColores;
}



// Verifica que el recoloreo se correcto
u32 RecoloreoCardinalidadDecrecienteBC_check(u32 n,u32* Coloreo, u32* NuevoColoreo){
    // Contar las repiticiones de cada color en Coloreo, guardando en array ReptColor
    u32 cantColores = 0;
    // ReptColor contiene la repetici??n de cada color
    Tuple * ReptColor = SumaRepeticionesColor(n, Coloreo, &cantColores);
    //printf("cantColor: %lu \n",cantColores);

    /*
    for(u32 i=0;i<cantColores;i++){
        printf("color: %lu; cant: %lu \n", ReptColor[i]->v2, ReptColor[i]->v1);
    }
    */

    // Iterar NuevoColoreo restando las veces que aparece un color en ReptColor
    for(u32 i=0; i<n; i++){
        ReptColor[NuevoColoreo[i]]->v1 -= 1; 
    }


    // Verificar que ReptColor tenga todas sus celdas en cero
    for(u32 i=0; i<cantColores; i++){
        if(ReptColor[i]->v1 != 0){
            printf("ERROR: Hay colores de menos\n");
            printf("Color: %lu, Cantidad: %lu \n", ReptColor[i]->v2, ReptColor[i]->v1);
            // Liberamos espacios
            for(u32 i=0; i<cantColores; i++){
                free(ReptColor[i]);
                ReptColor[i] = NULL;
            }
            free(ReptColor);
            ReptColor = NULL;
            return 0;
        }
    }

    // Liberamos los arrays usados
    for(u32 i=0; i<cantColores; i++){
        free(ReptColor[i]);
        ReptColor[i] = NULL;
    }
    free(ReptColor);
    ReptColor = NULL;

    return 1;
}
