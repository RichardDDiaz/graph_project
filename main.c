#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "EstructuraGrafo.h"
//#include "parser.h"

int main(){
    printf("Proyecto GRAFO iniciado");
    Grafo g = ConstruccionDelGrafo();
    if(g!=NULL){
        printf("== fun Numero Vertices: %lu ==\n", NumeroDeVertices(g));
        printf("== fun Numero Lados: %lu ==\n", NumeroDeLados(g));
        printf("== fun Delta: %lu ==\n", Delta(g));

        DestruccionDelGrafo(g);
        return 0;
        
    }
    else{
        printf("\n No se pudo construir el grafo. \n");
        return 0;
    }
    
}
