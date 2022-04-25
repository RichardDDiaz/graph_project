#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "AlduinPaarthurnaxIrileth.h"


/*
La funcion escribe en el lugar i de Coloreo[] cual es el color que 
Greedy le asigna al vertice cuyo  ́ındice es i en el Orden Natural.

Orden es un arreglo de numeros que representan las posiciones de los
en el orden natural.

Se asume una biyeccion entre la longitud de los dos arreglos Orden y 
Coloreo, con la cantidad de vertices

La funcion devuelve la cantidad de colores que Greedy asigno.
*/
u32 Greedy(Grafo G,u32* Orden,u32* Coloreo){
    u32  k = 1;
	u32 nColores = 1;
    u32 * conjuntoColoresUsados = NULL; //conjunto de colores usados en cada vertice
    // Inicializar arreglo Coloreo con -1
    for(u32 i = 0; i < NumeroDeVertices(G); i++){Coloreo[i] = -1;}

    // asignar el primer color al primer vertice en el arreglo Orden
    Coloreo[Orden[0]] = 0;

    // para cada numero k en Orden de indice i
    for(u32 i = 1; i < NumeroDeVertices(G); i++){
        u32 totalColoresUsadosK = 0;
		u32 indiceVecinosK = 0;
		u32 colorVecinoK = 0;
        // tomar el vertice en posicion natural k del grafo G
        k = Orden[i];
        // crear un conjunto con longitud de los colores usados hasta ese momento
        conjuntoColoresUsados = malloc(nColores * sizeof(u32));
        // Inicializar con -1
        for(u32 j = 0; j < nColores; j++){conjuntoColoresUsados[j] = -1lu;}
        // chequear los colores disponibles que no usarson sus vecinos
        while(totalColoresUsadosK < nColores && indiceVecinosK < Grado(k,G)){
            colorVecinoK = Coloreo[IndiceONVecino(indiceVecinosK, k, G)];
            if (colorVecinoK != -1lu){
                // significa que si esta coloreado
                conjuntoColoresUsados[colorVecinoK] = 1;
                totalColoresUsadosK++;
            }
            indiceVecinosK++;
        }
        //salis cuando o bien usaste todos los colores disponibles o 
        // recorriste todos los vecinos (quedan colores libres)

        // si usaste todos los colores disponibles
        if (totalColoresUsadosK == nColores){
            // crear un nuevo color
            nColores++;
            // asignarlo al vertice en posicion natural k, osea poner
            // el color nuevo en la posicion k del arreglo Coloreo
            Coloreo[k] = nColores-1; //los colores van desde el 0.
        }
        else {
            // buscar el primer color libre
            for(u32 j = 0; j < nColores; j++){
                if (conjuntoColoresUsados[j] == -1lu){
                    // asignarlo al vertice en posicion natural k, osea poner
                    // el color nuevo en la posicion k del arreglo Coloreo
                    Coloreo[k] = j;
                    break;
                }
            }
        }
        // liberar conjuntoColoresUsados
        free(conjuntoColoresUsados);
    }
    return nColores;
}
