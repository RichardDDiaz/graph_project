#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "AlduinPaarthurnaxIrileth.h"
#include "EstructuraGrafo.h"
#include "helpers.h"

int main(){

    /*-------------------------Consideraciones---------------------------------*/
    /*
    # Si hay un error de alocación retorna NULL.
    # Si Coloreo tenia Coloreo[i]=4 y ahora se cambia 4 por 7, entonces NuevoColoreo[i]=7,
      tambien para todos los i con color=4.
    # Debe ser un algoritmo que demore un tiempo razonable.
    */

    /*------------------------- PermutarColores -------------------------------*/
    // Caso básico
    u32 n = 5;
    u32 R = 105;
    u32 * Coloreo = malloc(sizeof(u32) * 5);

    Coloreo[0] = 0;
    Coloreo[1] = 1;
    Coloreo[2] = 2;
    Coloreo[3] = 3;
    Coloreo[4] = 4;

    printf("Permutar colores:\n");
    u32 * NuevoColoreo = PermutarColores(n,Coloreo,R);
    u32 result = permutarColores_cheeck(Coloreo, NuevoColoreo, n);
    if(result == 1){
        printf("== PermutarColores: OK ==\n");
    }
    else{
        printf("== PermutarColores: ERROR ==\n");
    }


    /*-------------------------------------------------------*/

    return 0;
}
