#ifndef _HELPER_H
#define _HELPER_H

#include "EstructuraGrafo.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

struct _Tuple{
    u32 v1;
    u32 v2;
};

typedef struct _Tuple * Tuple;


// estructura para queue
struct _Queue{
    u32 value;
    struct _Queue * next;
    struct _Queue * prev;
};

typedef struct _Queue * Queue;


//funcion para ser usada por qsort:
// compara los valores v1 y v2 de los tuplas 
// para ordenarlas de mayor a menor
int compararTuplas(const void * a, const void * b);

void enqueue(Queue *queue, Queue *lastElem, u32 value);

u32 dequeue(Queue *queue, Queue *lastElem);

void freeQueue(Queue *queue);

u32 coloreoBipartitoConexo(Grafo G, u32 *Coloreo, u32 index);


//return 1 si el coloreo es propio, 0 caso contrario.
u32 greedy_check(Grafo g, u32 * Coloreo, u32 nColores);


int ordenfromkey_check(u32 n,u32* key,u32* Orden);

int bipartito_check(Grafo g, u32 * Coloreo);

u32 permutarColores_cheeck(u32 * Coloreo, u32 * NuevoColoreo, u32 n);

u32 RecoloreoCardinalidadDecrecienteBC_check(u32 n,u32* Coloreo, u32* NuevoColoreo);

#endif
