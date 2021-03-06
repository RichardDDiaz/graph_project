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

    u32 alfa = (u32)atoi(a);
    u32 beta = (u32)atoi(b);
    u32 phi = (u32)atoi(p);

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
        fputs("\nGrafo bipartito", stdout);
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
        free(coloreoB);
    } else {
        fputs("\nGrafo no bipartito", stdout);
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

    // crear un arreglo de punteros de longitud (atoi(a) + 2) para guardar los alfaOrdenamientos
    fputs("\nParte 5:",stdout);
    u32 ** alfaOrdenamientos = (u32 **)malloc(sizeof(u32 *) * (alfa + 2));
    for (u32 i = 0; i < alfa + 2; i++) {
        alfaOrdenamientos[i] = (u32 *)malloc(sizeof(u32) * NumeroDeVertices(g));
        if(alfaOrdenamientos[i] == NULL){
            fputs("\nError Pt5 de asignación de memoria en alfaOrdenamientos[i]",stdout);
            return 1;
        }
    }
    // orden natural posicion 0
    for (u32 i = 0; i < NumeroDeVertices(g); i++) {
        alfaOrdenamientos[0][i] = i;
    }
    // orden Welsh-Powell posicion 1 -- CHEQUEAR
    u32 * key_grados = (u32 *)malloc(sizeof(u32) * NumeroDeVertices(g));
    for (u32 i = 0; i < NumeroDeVertices(g); i++) {
        key_grados[i] = Grado(i, g);
    }
    OrdenFromKey(NumeroDeVertices(g), key_grados, alfaOrdenamientos[1]);
    free(key_grados);
    // orden aleatorio posicion 2 a (alfa + 1)
    u32 * key_aleatorio = (u32 *)malloc(sizeof(u32) * NumeroDeVertices(g));
    for (u32 i = 2; i < alfa + 2; i++) {
        AleatorizarKeys(NumeroDeVertices(g), phi, key_aleatorio);
        OrdenFromKey(NumeroDeVertices(g), key_aleatorio, alfaOrdenamientos[i]);
    }
    free(key_aleatorio);


    /* 6. Para cada uno de esos α + 2 ordenamientos iniciales debe correr Greedy 
        e imprimir cuantos colores se obtienen. */
    
    // crear un arreglo de punteros de longitud (alfa + 2) para guardar los coloreos
    fputs("\n\nParte 6:",stdout);
    u32 ** colores = (u32 **)malloc(sizeof(u32 *) * (alfa + 2));
    for (u32 i = 0; i < (alfa + 2); i++) {
        colores[i] = (u32 *)malloc(sizeof(u32) * NumeroDeVertices(g));
        if(colores[i] == NULL){
            fputs("\nError: Asignación de memoria en colores.\n",stdout);
            return 1;
        }
    }

    u32 * indiceMayorColor = malloc(sizeof(u32)*NumeroDeVertices(g)); //reordenb
        if(indiceMayorColor == NULL){
            fputs("ERROR: Asignación de memoria a indiceMayorColor",stdout);
            return 1;
        }
    u32 * coloreoGreddy = malloc(sizeof(u32)*NumeroDeVertices(g));
        if(coloreoGreddy == NULL){
            fputs("ERROR: Asignación de memoria a coloreoGreddy",stdout);
            return 1;
        }
    
    u32 * reorden = malloc(sizeof(u32)*NumeroDeVertices(g));
        if(reorden == NULL){
            fputs("ERROR: Asignación de memoria a reorden",stdout);
            return 1;
        }

    u32 * coloreoFinal =  malloc(sizeof(u32)*NumeroDeVertices(g));
        if(coloreoFinal == NULL){
            fputs("ERROR: Asignación de memoria a coloreoFinal",stdout);
            return 1;
        }


    
    u32 ncolores = ErrorGrafo;
    for (u32 i = 0; i < alfa+2; i++) {
        // correr greedy para cada orden alfa
        u32 cantColores = Greedy(g, alfaOrdenamientos[i], colores[i]);
        char numColor[cantColores+2];
        char numOrden[i+1];
        fputs("\nColores orden de n°", stdout); sprintf(numOrden, "%lu", i+1);
        fputs(numOrden, stdout); fputs(": ", stdout);
        sprintf(numColor, "%lu", cantColores); fputs(numColor, stdout);

        u32 cantColoresAnteriores = cantColores;

        //copiar en coloreoGreddys los colores de colores[i]
        for (u32 k = 0; k < NumeroDeVertices(g); k++) {
            coloreoGreddy[k] = colores[i][k];
        }

        for(u32 j=0; j<beta; j++){ 


            // Parte a

            // Reordenamos segun el color de Mayor a menor
            OrdenFromKey(NumeroDeVertices(g), coloreoGreddy, indiceMayorColor);
            
            // Parte b
            cantColores = Greedy(g, indiceMayorColor, coloreoGreddy);

            char numColor[cantColores+1];
            fputs("\nCantidad de coloresOFK: ",stdout);
            sprintf(numColor, "%lu", cantColores); 
            fputs(numColor,stdout);
            
            // Chequeamos si aumento la cantidad de colores usados
            if(cantColores > cantColoresAnteriores){
                fputs("\nPt6 - b: ERROR: Se aumento la cantidad de colores.", stdout);
                fputs("\nCantidad de colores anteriores: ",stdout);
                sprintf(numColor, "%lu", cantColoresAnteriores); 
                fputs(numColor,stdout);
                return 1;
            }
            else{
                cantColoresAnteriores = cantColores;
            }
            // parte c
            u32 * keyPC = PermutarColores(NumeroDeVertices(g), coloreoGreddy, phi);
            OrdenFromKey(NumeroDeVertices(g),keyPC, reorden);
            free(keyPC);

            // parte d
            cantColores = Greedy(g, reorden, coloreoGreddy);
            char numColor2[cantColores+1];
            fputs("\nCantidad de coloresPC-OFK: ",stdout);
            sprintf(numColor2, "%lu", cantColores); 
            fputs(numColor2,stdout);
            
            // Chequemos si aumento la cantidad de colores usados
            if(cantColores > cantColoresAnteriores){
                fputs("\nPt6 - d: ERROR: Se aumento la cantidad de colores.", stdout);
                fputs("\nCantidad de colores anteriores: ",stdout);
                sprintf(numColor2, "%lu", cantColoresAnteriores); 
                fputs(numColor2,stdout);
                return 1;
            }
            else{
                cantColoresAnteriores = cantColores;
            }

            // parte e
            /*
            u32  * keyBC = RecoloreoCardinalidadDecrecienteBC(NumeroDeVertices(g), coloreoGreddy);
            OrdenFromKey(NumeroDeVertices(g), keyBC, reorden);
            free(keyBC);

            // parte f
            cantColores = Greedy(g, reorden, coloreoGreddy);
            char numColor3[cantColores+1];
            fputs("\nCantidad de coloresBC-OFK: ",stdout);
            sprintf(numColor3, "%lu", cantColores); 
            fputs(numColor3,stdout);
            
            // Chequemos si aumento la cantidad de colores usados
            if(cantColores > cantColoresAnteriores){
                fputs("\nPt6 - e: ERROR: Se aumento la cantidad de colores.", stdout);
                fputs("\nCantidad de colores anteriores: ",stdout);
                sprintf(numColor3, "%lu", cantColoresAnteriores); 
                fputs(numColor3,stdout);
                return 1;
            }
            else{
                cantColoresAnteriores = cantColores;
            }
            */
        }


        
        fputs("\nParte 7",stdout);
        // Verificamos si el color obtenido es mejor que el del alfa ordenamiento inicial
            if(cantColores < ncolores){
                // Copiamos el arreglo como el coloreo final
                for(u32 k=0; k<NumeroDeVertices(g); k++){
                    coloreoFinal[k] = coloreoGreddy[k];
                }
                ncolores = cantColores;
                fputs("\nNuevo Mejor Coloreo",stdout);
            }
            else {
                fputs("\nManteniendo el mejor coloreo actual",stdout);
            }
    }


    
    
    fputs("\nParte 8:\n",stdout);
    for(u32 i=0; i<((alfa+1)*3*beta); i++){
        OrdenFromKey(NumeroDeVertices(g), coloreoFinal, indiceMayorColor);
        u32 cantColores = Greedy(g, indiceMayorColor, coloreoGreddy);
        char numColor1[cantColores+1];
        fputs("\nCantidad de colores: ",stdout);
        sprintf(numColor1, "%lu", cantColores);
        fputs(numColor1,stdout);
        if(cantColores < ncolores){
            // Copiamos el arreglo
            for(u32 k=0; k<NumeroDeVertices(g); k++){
                coloreoFinal[k] = coloreoGreddy[k];
            }
            ncolores = cantColores;
        }
        else if (cantColores > ncolores){
            printf("\nPt8: ERROR: Se aumento la cantidad de colores.");
            return 1;
        }


        u32 * keyPC = PermutarColores(NumeroDeVertices(g), coloreoGreddy,phi);
        OrdenFromKey(NumeroDeVertices(g), keyPC, reorden);
        free(keyPC);
        cantColores = Greedy(g, reorden, coloreoGreddy);
        char numColor2[cantColores+1];
        fputs("\nCantidad de colores: ",stdout);
        sprintf(numColor2, "%lu", cantColores);
        fputs(numColor2,stdout);
        if(cantColores < ncolores){
            // Copiamos el arreglo
            for(u32 k=0; k<NumeroDeVertices(g); k++){
                coloreoFinal[k] = coloreoGreddy[k];
            }
            ncolores = cantColores;
        }
        else if (cantColores > ncolores){
            printf("\nPt8: ERROR: Se aumento la cantidad de colores.");
            return 1;
        }

        /*
        u32  * keyBC = RecoloreoCardinalidadDecrecienteBC(NumeroDeVertices(g), coloreoGreddy);
        ordenfromkey(NumeroDeVertices(g), keyBC, reorden);
        free(keyBC);
        cantColores = Greedy(g, reorden, coloreoGreddy);
        char numColor3[cantColores+1];
        fputs("\nCantidad de colores: ",stdout);
        sprintf(numColor3, "%lu", cantColores);
        fputs(numColor3,stdout);
        if(cantColores < cantColoresAnteriores){
            // Copiamos el arreglo
            for(u32 k=0; k<NumeroDeVertices(g); k++){
                coloreoFinal[k] = coloreoGreddy[k];
            }
            cantColoresAnteriores = cantColores;
        }
        else if (cantColores > cantColoresAnteriores){
            printf("\nPt8: ERROR: Se aumento la cantidad de colores.");
            return 1;
        }
        */
    }

    // Parte 9
    // imprimir con puts cual es la cantidad de colores obtenido
    char numColorFinal[ncolores+1];
    fputs("\nCantidad de colores finales: ",stdout);
    sprintf(numColorFinal, "%lu", ncolores);
    fputs(numColorFinal,stdout);
    //imprimir cuantos greedys se hicieron
    //(a + 2) * b + (alfa+1)*3*beta: creo que seria el numero de iteraciones








    
    // destruir grafo, liberar toda la memoria usada
    DestruccionDelGrafo(g);
    for (u32 i = 0; i < alfa + 2; i++) {
        free(alfaOrdenamientos[i]);
        free(colores[i]);
    }
    free(alfaOrdenamientos);
    free(colores);

    free(coloreoGreddy);
    free(reorden);
    free(coloreoFinal);
    free(indiceMayorColor);


    return 0;
}
