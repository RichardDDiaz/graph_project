#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "parser.h"


#define UNASSIGNED_COLOR 4294967295
#define ERROR 4294967295


//Iniciamos todos los espacios de memoria en NULL
void inicializarNullVertices(Grafo g){
    for(u32 i = 0; i < g->nver; i++){
        g->vertices[i] = NULL;
    }
}


Vertice crearDefaultVertice(u32 nombreVertice){
    Vertice v = malloc(sizeof(struct _VerticeSt));
    v->nombrev = nombreVertice;
    v->gradov = 0;
    v->colorv = UNASSIGNED_COLOR;
    v->vecinos = NULL; // vecinos = mmalloc (size de Vertice * delta de v)
    return v;
}


// Busca/crea el vertice 
Vertice buscarVertice(Grafo g, u32 nombreVertice){
    /* Funcion hash: un simple u32 % nver */
    // [0,...,key_hash,...,nver-1]
    u32 key_hash = nombreVertice % g->nver;

    if (g->vertices[key_hash] == NULL){
        //printf("hash == NULL\n");
        //crear el vertice
        g->vertices[key_hash] = crearDefaultVertice(nombreVertice);
        return g->vertices[key_hash];
    }
    // al finalizar este ciclo o la funcion retorno el vertice
    // por que lo encontro o salio del ciclo porque 
    // encontro una celda vacia
    //printf("pre while -> hash != NULL\n");
    while(g->vertices[key_hash] != NULL){
        
        // Si ya existe el vertice
        //printf("on while -> pre if;  key_hash: %lu;  nombreV: %lu\n", key_hash, g->vertices[key_hash]->nombrev);
        if(g->vertices[key_hash]->nombrev == nombreVertice){
            return g->vertices[key_hash];
        }
        key_hash = key_hash + 1;
        key_hash = key_hash % g->nver;
    }
    // si salis del ciclo pero no de la funcion, significa que 
    // encontraste una celda vacia => no existe el vertice
    // nombreVertice, por que por ejemplo si en la interacion anterior 
    // uno de los lados era nombreVertice, entonces esta celda libre
    // que fue la primera que encontramos, deberia tener a nombreVertice
    g->vertices[key_hash] = crearDefaultVertice(nombreVertice);
    //printf("post while -> hash != NULL\n");
    return g->vertices[key_hash];
}


// Establece la vecindad entre dos vecinos
void emparejarVertices(Vertice verticeA,Vertice verticeB){
    // Aumentamos el grado de los vertices
    verticeA->gradov = verticeA->gradov + 1;
    verticeB->gradov = verticeB->gradov + 1;

    u32 gradoA = verticeA->gradov;
    u32 gradoB = verticeB->gradov;

    // Reasignar el arreeglo de vecinos
    verticeA->vecinos = realloc(verticeA->vecinos, sizeof(Vertice) * gradoA);
    verticeB->vecinos = realloc(verticeB->vecinos, sizeof(Vertice) * gradoB);

    // Enlasamos los vecinos
    verticeA->vecinos[gradoA-1] = verticeB;
    verticeB->vecinos[gradoB-1] = verticeA;

}



// Compara los vertices indicando cual es mayor
int cmpfunc (const void * a, const void * b) {
  Vertice al =*((Vertice*)a);
  Vertice bl =*((Vertice*)b);

  if (al->nombrev < bl->nombrev){
    return -1;
  }
  
  if (al->nombrev > bl->nombrev){
    return 1;
  }else{
    return 0;
  }
}



/*
Ejecucion de la carga de datos en un grafo g, apartir de un archivo de texto
pasado por consola.
*/
bool run_parser(Grafo g){
    char path_name[100];
    printf("\n Indique ruta del archivo: \n");
    int scan_path_name = scanf("%s", path_name);
    printf("filename: %s\n", path_name);
    if (scan_path_name <= 0){
        printf("Error al leer ruta del archivo");
        DestruccionDelGrafo(g);
        return false;
    }

    FILE *file = fopen(path_name, "r");
    if (file == NULL){
        printf("Error al abrir archivo");
        DestruccionDelGrafo(g);
        return false;
    }
    printf("Archivo Abierto\n");
    
    // leer  el primer caracter del archivo
    char firstchar;
    int count_fscanf = fscanf(file,"%c", &firstchar);
    
    /* recorre los comentarios cuando el primer caracter es 'c' 
       cuando el primer caracter sea != de 'c', en teoria ya estamos
       en la parte de lectura de los lados */
    while(!feof(file) && firstchar == 'c'){
        while(firstchar != EOF && firstchar != '\n'){
            fscanf(file,"%c", &firstchar);
        }
        // te paras en el siguiente primer caracter
        fscanf(file,"%c", &firstchar);
    }

    u32 nver;
    u32 mlado;
    char pseudo_edge[5]; // +1 por caracter de terminación
    // si el primer caracter es EOF, no hay mas datos
    if (firstchar != 'p' || 
        fscanf(file,"%s %lu %lu",pseudo_edge , &nver, &mlado) <= 0 ||
        strcmp("edge",pseudo_edge)){
        
        printf("Error en formato de entrada linea p \n");
        DestruccionDelGrafo(g);
        return false;
    }


    printf("%lu vertices y %lu Lados\n", nver, mlado);

    g->nver = nver;
    g->mlados = mlado;
    g->vertices = malloc(sizeof(Vertice) * nver);
    inicializarNullVertices(g);
    g->vertOrdNat = malloc(sizeof(Vertice) * nver);
    g->delta = 0;

    // lectura de los lados con vertices
    // formato de cada linea: e v1 v2
    u32 vA, vB;
    u32 count_m = 0u;
    while(count_m <= mlado-1){
        //printf("while\n");
        /*
            cuando hacemos fscanf(file,"%s %lu %lu",pseudo_edge , &nver, &mlado)
            el siguiente fscanf tomara el salto de linea de la linea j-1
            y el siguiente fscanf sera el primer char de la linea j.
            no se como hacer para que lo ignore sin hacer que lo asigne a una 
            variable que no usaremos(lo probe con la var u32 vA y tampoco)
        */
        fscanf(file,"%c", &firstchar);
        u32 check_scan = fscanf(file,"%c", &firstchar);
        //printf("firstchar: %c \n",firstchar);
        // estas al final de archivo o Error de lectura
        if (check_scan == EOF){
            printf("Warning: Debia leer %lu lados, leyo solo %lu\n",
                    mlado, count_m);
            DestruccionDelGrafo(g);
            return false;
            
        }
        // la linea cumple el formato: e v w 
        else if (firstchar == 'e' && fscanf(file,"%lu %lu", &vA, &vB) > 0){
            // retorna puntero al vertice creado o encontrado
            Vertice verticeA = buscarVertice(g, vA);
            Vertice verticeB = buscarVertice(g, vB);
            //agregar vertice como vecino de otro y viceversa.
            emparejarVertices(verticeA, verticeB);
            if(verticeA->gradov > g->delta){
                g->delta = verticeA->gradov;
            }
            if(verticeB->gradov > g->delta){
                g->delta = verticeB->gradov;
            }
            count_m++;
        }
        // la linea no lo cumple el formato
        else{
            printf("ERROR: Linea no cumple el formato (e v1 v2)"
            "en el lado %lu\n", count_m);
            DestruccionDelGrafo(g);
            return false;
        }
    }
    
    // Orden Natural
    printf("Orden natural \n");
    qsort(g->vertices, g->nver, sizeof(Vertice), cmpfunc);
    return true;
}
