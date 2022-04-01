#ifndef _HELPER_H
#define _HELPER_H

#include "EstructuraGrafo.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

struct _VertHash{
  Vertice vertice;
  u32 estado;
};

typedef struct _VertHash * VertHash;

#endif