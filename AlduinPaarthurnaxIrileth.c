#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "helpers.h"
#include "AlduinPaarthurnaxIrileth.h"
#define ErrorGrafo 4294967295


u32* Bipartito(Grafo G){ 
    u32* Coloreo = (u32*)malloc(NumeroDeVertices(G)*sizeof(u32));

    //inicializar coloreo con ERRORGRAFO
    for (u32 i=0; i < NumeroDeVertices(G); i++){
        Coloreo[i] = ErrorGrafo;
    }
    
    u32 index = 0;
    while (index < NumeroDeVertices(G)){
        if (Coloreo[index] == ErrorGrafo){
            if (coloreoBipartitoConexo(G, Coloreo, index) != 1){
                free(Coloreo);
                return NULL;
            }
        }
        else {
            index++;
        }
    }

    return Coloreo;
}



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
    if (G == NULL || Orden == NULL || Coloreo == NULL){
        return ErrorGrafo;
    }

    u32  k = 0;
	u32 nColores = 1;
    //conjunto de colores usados en cada vertice
    u32 * conjuntoColoresUsados = NULL;
    // Inicializar arreglo Coloreo con ErrorGrafo
    for(u32 i = 0; i < NumeroDeVertices(G); i++){Coloreo[i] = ErrorGrafo;}

    // para cada numero k en Orden de indice i
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
        u32 totalColoresUsadosK = 0;
		u32 indiceVecinosK = 0;
		u32 colorVecinoK = 0;
        // tomar el vertice en posicion natural k del grafo G
        k = Orden[i];
        // crear un conjunto con longitud de los colores usados hasta ese momento
        conjuntoColoresUsados = calloc(nColores, sizeof(u32));
        // chequear los colores disponibles que no usarson sus vecinos
        while(totalColoresUsadosK < nColores && indiceVecinosK < Grado(k,G)){
            colorVecinoK = Coloreo[IndiceONVecino(indiceVecinosK, k, G)];
            if (colorVecinoK < nColores && 
                    conjuntoColoresUsados[colorVecinoK] == 0){
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
                if (conjuntoColoresUsados[j] == 0){
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
    conjuntoColoresUsados = NULL;
    return nColores;
}



/*  array apuntado por key, el cual se asume que es de longitud n.
    se llena el array al cual apunta Orden, el cual se asume que tiene 
        suficiente memoria para al menos n entradas.
    asume que el rango de key es n o menor, es decir key[i]≤ n para todo i.

    """Lo que NO se asume, 
    y de hecho casi nunca sera cierto, es que key sea una biyeccion."""

    Debe llenar Orden de forma tal que en el lugar 0 vaya el  indice i0 
    tal que key[i0] sea el maximo de todos los valores key[i].
    "Notar que dice el indice no el valor de key[i]"

    obtener el indice del mayor valor del arreglo key y guardar en i0
    del arreglo de orden, y asi para cada indice
*/
char OrdenFromKey(u32 n,u32* key,u32* Orden){
    // crear arreglo de Tuple con malloc
    Tuple * arregloTuplas = malloc(n*sizeof(Tuple));
    if (arregloTuplas == NULL){return '1';}
    // llenar arregloTuplas con los valores de key en v1 e indices en v2
    for(u32 i = 0; i < n; i++){
        arregloTuplas[i] = malloc(sizeof(struct _Tuple));
        arregloTuplas[i]->v1 = key[i]; //valor del key
        arregloTuplas[i]->v2 = i; //indice de ese valor
    }


    //ordenar usando qsort y la funcion compararTuplas
    qsort(arregloTuplas, n, sizeof(Tuple), compararTuplas);
    
    //almacenar los indices ordenados en Orden
    for(u32 i = 0; i < n; i++){
        Orden[i] = arregloTuplas[i]->v2;
        // imprimir key y indice
    }

    //liberar arregloTuplas
    for(u32 i = 0; i < n; i++){
        free(arregloTuplas[i]);
    }
    free(arregloTuplas);
    arregloTuplas = NULL;
    return '0';
}



// Setea cada posición de key con un nuevo valor aleatorio usando la semilla R
void AleatorizarKeys(u32 n,u32 R,u32* key){
    u32 ra1= rand();
    u32 ra2= rand();
    u32 ra3 = 0;
    
    for(u32 i=0; i<n; i++){
        // seteamos la semilla R
        srand(R+i);
        // Obtenemos los numeros random
        ra1= (u32)rand() +1;
        ra2= (u32)rand();
        ra3 = (u32)(ra1 + ra2);
        key[i] = ra3 % n;
    }
}

// retorna el color i de ColorNat si esta disponible y actualiza el color
// a utilizar en control, si no esta disponible iteramos por Coloreo hasta encontrar uno.
// control[k]==1 color usado; control[k]==0 color
//u32 buscarColor(u32 * control, u32 i, u32 * colorNat, u32 cantColor){
u32 buscarColor(u32 * colorNat, u32 i,u32 * control, u32 cantColor){
    // retornamos el color disponible
    if(control[i]==0){
        control[i] = 1;
        return colorNat[i];
    }
    // buscamos linealmente uno disponible
    else{
        u32 j = i;
        do{
            j = (j+1) % cantColor;
        }while(control[j] == 1);
        // seteamos el color a usar en 1 "no usable"
        control[j] = 1;
        // retornamos color encontrado disponible
        return (colorNat[j]);
    }
}



// Permuta cada color de coloreoNuevo por uno de Coloreo de manera pseudo-aleatoria con 
// la semilla R.
u32* PermutarColores(u32 n,u32* Coloreo,u32 R){
    u32 cantColores = 0;

    // colores en orden natural
    u32 * colorNat = malloc(sizeof(u32));
    colorNat[cantColores] = 0;

    // copiamos coloreo
    u32 * coloreoNuevo = malloc(sizeof(u32)*n);
    for(u32 i=0; i<n; i++){
        // actualizamos la cantidad de colores
        if(cantColores <  (Coloreo[i])){
            cantColores = Coloreo[i];

            // agregamos un nuevo color en orden natural
            colorNat = realloc(colorNat, sizeof(u32) * (cantColores+1));
            colorNat[cantColores] = cantColores;
        }
        coloreoNuevo[i] = Coloreo[i];
    }

    // +1 para obtener la cantidad de colores total
    cantColores += 1;

    // Establecer arrays de aleatoriedad con semilla R
    // keyColor obtendra la posición en que se consultara las celdas de colorNat
    u32 * keysColor = malloc(sizeof(u32)*cantColores);
    AleatorizarKeys(cantColores,R,keysColor);

    // controlColor: 0=color disponible en array colorNat; 1=color no disponible
    u32 * controlColor = malloc(sizeof(u32)*cantColores);
    // perColor: resultado de la biyección de permutar los colorNat
    u32 * perColor = malloc(sizeof(u32)*cantColores);
    for(u32 i=0; i< cantColores; i++){
        perColor[i] = 0;
        controlColor[i] = 0;
    }

    // Permutar los colores
    for(u32 i=0; i<cantColores; i++){
        // buscamos el color disponible
        perColor[i] = buscarColor(colorNat, keysColor[i],controlColor, cantColores);
    }
    printf("\n Colores Permutados:");
    for(u32 i=0; i<cantColores; i++){
        printf(",%lu ", perColor[i]);
    }

    // Liberar los arreglos
    free(colorNat);
    colorNat = NULL;
    free(coloreoNuevo);
    coloreoNuevo = NULL;
    free(keysColor);
    keysColor = NULL;
    
    return coloreoNuevo;

}

/*
  Retorna NuevoColoreo con los indices coloreados de la forma:
    Los primeros n0 indices coloreados con el color k más repetido en Coloreo,
    Luego los n1 indices coloreados con m segundo más repetido en Coloreo, etc.
*/
u32* RecoloreoCardinalidadDecrecienteBC(u32 n,u32* Coloreo){
    Tuple * nColores = malloc(sizeof(Tuple));
    if (nColores == NULL){return NULL;}
    nColores[0] = malloc(sizeof(struct _Tuple));
    if (nColores[0] == NULL){return NULL;}
    nColores[0]->v1 = 0; //cantidad del color
    nColores[0]->v2 = 0; //color

    u32 cantColores = 0;
    // Sumamos las veces que aparece cada color
    for(u32 i=0; i<n; i++){
        // Si encontramos un color nuevo
        if(cantColores < Coloreo[i]){
            // agrandamos el arreglo de colores
            nColores = realloc(nColores, sizeof(Tuple)*(Coloreo[i]+1));

            // seteamos en 0 el resto de colores
            for(u32 j=(cantColores +1); j<(Coloreo[i]+1);j++){
                nColores[j] = malloc(sizeof(struct _Tuple));
                if(nColores[j] == NULL){return NULL;}
                // Agregamos los nuevos colores entre el ultimo agregado y el nuevo encontrado
                nColores[j]->v1=0; // cantidad del color
                nColores[j]->v2=j; // color
            }
            cantColores = Coloreo[i];
        }
        // Sumamos 1 al color encontrado
        nColores[Coloreo[i]]->v1 += 1;
    }

    // agregamos uno por la cantidad total de colores
    cantColores +=1;

    // Ordenamos nColores de mayor a menor
    qsort(nColores, cantColores, sizeof(Tuple), compararTuplas);

    u32 * NuevoColoreo = malloc(sizeof(u32)*n);
    if(NuevoColoreo == NULL){return NULL;}

    u32 colorInx = 0;
    u32 index = 0;
    // Seteamos el nuevo coloreo
    for(u32 i=0; i<cantColores;i++){
        colorInx = nColores[i]->v1;
        for(u32 j=index;j<(index + colorInx); j++)
        {
            NuevoColoreo[j]=nColores[i]->v2;
        }
        index += colorInx;
    }

    // Liberamos los arrays usados
    for(u32 i=0; i<cantColores; i++){
        free(nColores[i]);
        nColores[i] = NULL;
    }
    free(nColores);
    nColores = NULL;
    
    return NuevoColoreo;
}
