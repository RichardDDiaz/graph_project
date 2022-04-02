#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "parser.h"

void main(){
    printf("Proyecto GRAFO iniciado");
    Grafo g = ConstruccionDelGrafo();
    assert(g != NULL && "Grafo es Null");
    printf("\n Construccion del grafo: Finalizada \n");
    
}