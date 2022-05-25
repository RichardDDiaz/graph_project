#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "parser.h"


//#define UNASSIGNED_COLOR 4294967295

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
    v->vecinos = NULL;
    return v;
}


// Busca/crea el vertice
Vertice buscarVertice(Grafo g, u32 nombreVertice){
    /* Funcion hash: un simple u32 % nver */
    // [0,...,key_hash,...,nver-1]
    u32 key_hash = nombreVertice % g->nver;

    if (g->vertices[key_hash] == NULL){
        //crear el vertice
        g->vertices[key_hash] = crearDefaultVertice(nombreVertice);

        return g->vertices[key_hash];
    }
    // al finalizar este ciclo o la funcion retorno el vertice
    // por que lo encontro o salio del ciclo porque
    // encontro una celda vacia
    while(g->vertices[key_hash] != NULL){

        // Si ya existe el vertice
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
//////////////////////////////////////////////////

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
    //char path_name[100];
    //char * nscanf = NULL;
    //char * c = fgets(path_name, 100, stdin);
    
    /*if (fgets(path_name, 100, stdin) == NULL){
        puts("Error al leer ruta del archivo");
        DestruccionDelGrafo(g);
        return false;
    } 
    else{
        puts("\n");
        puts(path_name);
    }*/
    //FILE *file = fopen(strtok(path_name, "\n"), "r");
    FILE *file = stdin;
    if (file == NULL){
        puts("Error al abrir archivo");
        DestruccionDelGrafo(g);
        //fclose(file);
        return false;
    }
    puts("Archivo Abierto\n");
    int firstchar;
    firstchar = fgetc(file);

    if(firstchar == EOF){DestruccionDelGrafo(g); fclose(file); return false;}

    /* recorre los comentarios cuando el primer caracter es 'c'
       cuando el primer caracter sea != de 'c', en teoria ya estamos
       en la parte de lectura de los lados */
    while(!feof(file) && firstchar == 'c'){
        while(firstchar != EOF && firstchar != '\n'){
            firstchar = fgetc(file);
            if(firstchar == EOF){DestruccionDelGrafo(g); fclose(file); return false;}
        }
        // te paras en el siguiente primer caracter
        firstchar = fgetc(file);
        if(firstchar == EOF){DestruccionDelGrafo(g); fclose(file); return false;}
    }

    u32 nver;
    u32 mlado;
    char * edge = NULL;
    char linea[80];

    //char pseudo_edge[5]; // +1 por caracter de terminación
    // si el primer caracter es EOF, no hay mas datos
    // fscanf(file,"%s %lu %lu",pseudo_edge , &nver, &mlado) 
    // fgets(pseudo_edge, 5, file);

    if (firstchar != 'p' || fgets(linea, 80, file) == NULL){
        puts("Error en formato de entrada linea p \n");
        DestruccionDelGrafo(g);
        fclose(file);
        return false;
    }

    // se puede chequear si alguno tiene null, pero no si lo que tiene es 
    //correcto
    edge = strtok(linea, " ");
    if(strcmp("edge", edge) != 0){
        DestruccionDelGrafo(g);
        fclose(file);
        return false;
    }
    nver = strtoul(strtok(NULL, " "), NULL, 10);
    mlado = strtoul(strtok(NULL, " "), NULL, 10);

    

    g->nver = nver;
    g->mlados = mlado;
    g->vertices = malloc(sizeof(Vertice) * nver);
    inicializarNullVertices(g);
    //g->vertOrdNat = malloc(sizeof(Vertice) * nver);
    g->delta = 0;


    u32 vA, vB;
    u32 count_m = 0u;

    while(count_m <= mlado-1){
        firstchar = fgetc(file);

        // caso donde no puede leer el archivo, por error o por que no hay mas
        if (firstchar == EOF){
            DestruccionDelGrafo(g);
            fclose(file);
            return false;
        }
        // caso donde si son numeros y debemos empezar a cargar los vertices
        else if (firstchar == 'e' && fgets(linea, 80, file) != NULL){
            vA = strtoul(strtok(linea, " "), NULL, 10);
            vB = strtoul(strtok(NULL, " "), NULL, 10);            
            //printf("vA: %lu, vB: %lu\n", vA, vB);

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
        // la linea no cumple el formato
        else{
            puts(strcat("Error en formato de entrada linea e:\n ", linea));
            DestruccionDelGrafo(g);
            fclose(file);
            return false;
        }
        
    }

    // ordenar de forma natural
    qsort(g->vertices, g->nver, sizeof(Vertice), cmpfunc);

    // setear la posición de los vertices
    for(u32 i=0; i<g->nver; i++){
        g->vertices[i]->positionOrdNat = i;
    }

    fclose(file);

    return true;
}
