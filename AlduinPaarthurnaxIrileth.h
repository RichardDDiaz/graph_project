#ifndef __API_H
#define __API_H


#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

//coloreantes

u32* Bipartito(Grafo  G);

u32 Greedy(Grafo G,u32* Orden,u32* Coloreo);

//ordenamiento a partir de clave

char OrdenFromKey(u32 n,u32* key,u32* Orden);

//claves aleatorias

void AleatorizarKeys(u32 n,u32 R,u32* key);


//permutadores de colores
u32* PermutarColores(u32 n,u32* Coloreo,u32 R);

u32* RecoloreoCardinalidadDecrecienteBC(u32 n,u32* Coloreo);




#endif