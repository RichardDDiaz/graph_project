#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "AlduinPaarthurnaxIrileth.h"
#include "EstructuraGrafo.h"
#include "helpers.h"

#define ErrorGrafo 4294967295

/*
1)
Para empezar deber ́a requerir 3 parametros enteros α, β, ρ. Esto debe ser hecho de forma 
tal que si compilamos a un ejecutable ejec podamos hacer
./ejec α, β, ρ <enter>
y luego cargar a mano el grafo, o bien poder usar el operador de redirecci ́on y hacer pej
./ejec α, β, ρ <q10.txt
donde q10.txt sea algun archivo con un grafo.

*/

int main(int argc,char* argv[]){
    //printf("Proyecto GRAFO iniciado");

    if (argc > 4){
        printf("Error en la cantidad de argumentos");
        return 1;
    }
    char * a = argv[1];
    char * b = argv[2];
    char * p = argv[3]; 
    /*-------------------------------------------------------*/
    fputs(a, stdout);
    fputs(b, stdout);
    fputs(p, stdout);

    // 2. Luego de cargar el grafo, imprime el n ́umero de v ́ertices, el n ́umero de lados y
    // Delta.

    Grafo g = ConstruccionDelGrafo();
    printf("grafo terminado\n");
    if(g!=NULL){
        char num[NumeroDeLados(g)];
        sprintf(num, "%lu", NumeroDeVertices(g));
        fputs("\nVertice: " , stdout); fputs(num , stdout);
        sprintf(num, "%lu", NumeroDeLados(g));
        fputs("\nLados: " , stdout); fputs(num , stdout);
        sprintf(num, "%lu", Delta(g));
        fputs("\nDelta: " , stdout); fputs(num , stdout);
    }

    /*
    3. Luego de eso, corre Bipartito() para ver si el grafo es bipartito o no. 
    Si lo es, declara eso y en caso que la cantidad de v ́ertices sea menor a 101, 
    imprime las dos partes del grafo y termina la ejecuci ́on. 
    Si no lo es, se declara eso y se continua con el resto
    */

    u32 * coloreoB = NULL;
    coloreoB = Bipartito(g);
    if(coloreoB!=NULL){
        fputs("\nGrafo bipartito\n", stdout);
        if(NumeroDeVertices(g)<101){
            //char num[ErrorGrafo-1];
            // color 1
            fputs("\nColoreados con 1: ", stdout);
            for (u32 i = 0; i < NumeroDeVertices(g); i++) {
                char num[Nombre(i, g)];
                if(coloreoB[i]==1){
                    sprintf(num, "%lu", Nombre(i, g));
                    fputs(num, stdout); fputs(", ", stdout);
                }
            }
            // color 2
            fputs("\nColoreados con 2: ", stdout);
            for (u32 i = 0; i < NumeroDeVertices(g); i++) {
                if(coloreoB[i]==2){
                    char num[Nombre(i, g)];
                    sprintf(num, "%lu", Nombre(i, g));
                    fputs(num, stdout); fputs(", ", stdout);
                }
            }
        }
    } else {
        fputs("\nGrafo no bipartito\n", stdout);
    }

    /*4. Para el resto de la corrida se usar ́an procesos pseudoaleatorios, 
    pej en AleatorizarVertices() uno de los parametros es R que funciona como semilla 
    de aleatoriedad. La fuente “inicial”de aleatoriedad a partir de la cual todas 
    las demas fuentes se vayan obteniendo ser ́a el par ́ametro ρ.*/

    /*5. Construye α + 2 ordenamientos iniciales como se explica a continuaci ́on:
    (a) Un orden se obtiene simplemente declarando Orden[i]=i, es decir, 
        es el orden natural.
    (b) Otro orden ser ́a el orden “Welsh-Powell”que consiste en ordenar los vertices 
        de mayor a menor grado. Este orden se obtiene usando OrdenFromKey a partir 
        de definir key[i]=Grado(i,G);
    (c) Los otros α ordenes se obtienen usando OrdenFromKey a partir de definir 
        key usando AleatorizarKeys con distintos Rs, generados a partir de ρ.*/

    // Matriz con todos los ordenamientos
    //u32 * alfaOrdenamientos[atoi(a) + 2][NumeroDeVertices(g)];

    
    //u32 ** alfaOrdenamientos = malloc(sizeof(u32 *) * (u32)(atoi(a) + 2));
    u32 * alfaOrdenamientos = malloc(sizeof *alfaOrdenamientos * (u32)(atoi(a) + 2));
    printf("\nsdfdfsff");

    if(alfaOrdenamientos == NULL){
            fputs("\nError: Malloc en alfaOrdenamientos \n",stdout);
            return 1;
    }
    for(u32 k=0; k<(u32)(atoi(a) + 2); k++){
        alfaOrdenamientos[k]= malloc(sizeof(u32)*NumeroDeVertices(g));
        if(alfaOrdenamientos[k] == NULL){
            fputs("\nError: Malloc en alfaOrdenamientos[] \n",stdout);
        }
    }


    u32 * array_order = alfaOrdenamientos[0];
    for(u32 j=0; j<NumeroDeVertices(g); j++){
        array_order[j] = j;
        
    }

    u32 * array_key = malloc(sizeof(u32)*NumeroDeVertices(g));
    for(u32 j=0; j<NumeroDeVertices(g); j++){
        array_key[j] = Grado(j,g);
    }
    OrdenFromKey(NumeroDeVertices(g), array_key, alfaOrdenamientos[1]);
    //for(u32 i=2; i<(u32)(atoi(a)+2); i++){

    //}


    // FREE
    for(u32 k=0; k<NumeroDeVertices(g); k++){
        free(alfaOrdenamientos[k]);
        alfaOrdenamientos[k]= NULL;
    }
    free(alfaOrdenamientos);
    alfaOrdenamientos = NULL;
    return 0;
}
