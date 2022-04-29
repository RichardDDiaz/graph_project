#ifndef _HELPER_H
#define _HELPER_H

#include "EstructuraGrafo.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

//return 1 si el coloreo es propio, 0 caso contrario.
u32 greedy_check(Grafo g, u32 * Coloreo, u32 nColores);

#endif