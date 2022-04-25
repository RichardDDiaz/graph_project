#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <AlduinPaarthurnaxIrileth.h>
#include <EstructuraGrafo.h>


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
    u32 nColores, k = 1;
    u32 * conjuntoColoresUsados = NULL //conjunto de colores usados en cada vertice
    // Inicializar arreglo Coloreo con -1
    for(u32 i = 0; i < NumeroDeVertices(G); i++){Coloreo[i] = -1}

    // asignar el primer color al primer vertice en el arreglo Orden
    Coloreo[Orden[0]] = 0;

    // para cada numero k en Orden de indice i
    for(u32 i = 1; i < NumeroDeVertices(G); i++){
        u32 totalColoresUsadosK, indiceVecinosK, colorVecinoK = 0;
        //  tomar el vertice en posicion natural k del grafo G
        k = Orden[i];
        // crear un conjunto con longitud de los colores usados hasta ese momento
        conjuntoColoresUsados = malloc(nColores * sizeof(u32));
        // Inicializar con -1
        for(u32 j = 0; j < nColores; j++){conjuntoColoresUsados[j] = -1}
        // chequear los colores disponibles que no usarson sus vecinos
        while(totalColoresUsadosK < nColores && indiceVecinosK < Grado(k,G)){
            colorVecinoK = Coloreo[IndiceONVecino(indiceVecinosK, k, G)]
            if (colorVecinoK != -1){
                // significa que si esta coloreado
                conjuntoColoresUsados[colorVecinoK] = 1;
                totalColoresUsadosK++;
                /*
                Por defecto el primer color no usado seria el 0
                entonces preguntar si ese color es el que se...

                Pero creo que no seria tan bueno.. investigar
                */
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
            Coloreo[k] = nColores;
        }
        else {
            // buscar el color mas pequeño no usado.. pero podria hacerlo de ante mano
        }

            

            // si el conjunto es vacio, colorearlo con el primer color disponible (color 0)
            // si no, colorearlo con el primer color que no sea usado por sus vecinos

        // asginar el menor color no usado o crear uno nuevo
    
    // LLenar el arreglo Coloreo luego

}