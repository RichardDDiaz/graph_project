#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "parser.h"

#define UNASSIGNED_COLOR 4294967295
#define ERROR 4294967295


Grafo ConstruccionDelGrafo()
{
	//creo un grafo y le reservo memoria
	Grafo g = malloc(sizeof(GrafoSt));
	//chequeo que malloc haya terminado exitosamente
    if (g == NULL) {
        printf("No hay suficiente memoria para el grafo :( )\n");
    }
	//inicializo los datos
	g->nver = 0;
	g->mlados = 0 ;
	g->ccolor = 0;
	g->delta  = 0;
	g->vertices = NULL;
    g->vertOrdNat = NULL;

	run_parser(g);
	return g;
}


//Iniciamos todos los espacios de memoria en NULL
void inicializarNullVertices(Grafo g){
    for(u32 i = 0; i < g->nver; i++){
        g->vertices[i] = NULL;
    }
}


// Busca/crea el vertice 
Vertice buscarVertice(Grafo g, u32 nombreVertice){
    /*
    Funcion hash: un simple u32 % nver 
    */
    //[0,...,key_hash,...,nver-1]
    u32 key_hash = nombreVertice % g->nver;

    if (g->vertices[key_hash] == NULL){
        //crear el vertice
        Vertice v = malloc(sizeof(struct _VerticeSt));
        v->nombrev = nombreVertice;
        v->gradov = 0;
        v->colorv = UNASSIGNED_COLOR;
        g->vertices[key_hash] = v;
        v->vecinos = NULL;
        return v;
    }
    //el else creo que lo podemos quitar por que hay un return en el IF
    else{
        //variable flag: si encuentro el vertice, cambio el valor de flag a 
        //la posicion de esa celda en el arreglo
        u32 kh_value_real = ERROR;
        
        // al finalizar este ciclo o la funcion retorno el vertice
        // por que lo encontro o salio del ciclo porque 
        // encontro una celda vacia
        while(g->vertices[key_hash] != NULL && kh_value_real == ERROR){
            // Si ya existe el vertice
            if(g->vertices[key_hash]->nombrev == nombreVertice){
                kh_value_real = key_hash;
                // no se si este return aqui es una buena practica
                // y no quiero usar un break o poner el kh_value_real = -2
                // por ejemplo, pero si tampoco quiero usar un if al finalizar
                // el ciclo para ver si encontre el vertice por que aqui lo 
                // encontre.

                //entonces si lo dejamos asi kh_value_real no haria falta
                //para nada de nada.
                return g->vertices[key_hash];
            }
            key_hash = (key_hash++) % g->nver;
        }
        //seguir buscando apartir de la posicion de la celda vacia,
        //pero no olviar que ya tenemos un posible lugar para el vertice
        u32 empty_cell = key_hash;
 
    /*
        // mientras no le diste la vuelta entra al ciclo.
        while(key_hash != (nombreVertice % g->nver)){
            // si encontras el vertice
            if(g->vertices[key_hash] != NULL 
                    && g->vertices[key_hash]->nombrev == nombreVertice){
                
                // no se si este return aqui es una buena practica
                // y no quiero usar un break
                return g->vertices[key_hash];
            }
            key_hash = (key_hash++) % g->nver;
        }
    */
        //si salis le diste la vuelta y no encontraste el vertice =>
        //crearlo y asignarlo a la posicion vacia
        Vertice v = malloc(sizeof(struct _VerticeSt));
        v->nombrev = nombreVertice;
        v->gradov = 0;
        v->colorv = UNASSIGNED_COLOR;
        v->vecinos = NULL; // vecinos = mmalloc (size de Vertice * delta de v)
        g->vertices[empty_cell] = v;
        
        return v;
    }
}

// Establece la vecindad entre dos vecinos
void emparejarVertices(Vertice verticeA,Vertice verticeB){
    // Aumentamos el grado de los vertices
    verticeA->gradov +=1;
    verticeB->gradov +=1;

    int gradoA = verticeA->gradov;
    int gradoB = verticeB->gradov;


    // Reasignar el arreeglo de vecinos
    verticeA->vecinos = realloc(verticeA->vecinos,gradoA );
    verticeB->vecinos = realloc(verticeB->vecinos,gradoB );

    // Enlasamos los vecinos
    verticeA->vecinos[gradoA-1] = verticeB;
    verticeB->vecinos[gradoB-1] = verticeA;


    // imprimimos vecinos de A
    printf("nombre vA: %lu \n grado: %lu\n", verticeA->nombrev, verticeA->gradov);
    for(int i=0; i<gradoA; i++){
        printf("vecino %i : %lu\n", i, verticeA->vecinos[i]->nombrev);
    }
    // imprimimos vecinos de B
    printf("nombre vA: %lu \n grado: %lu\n", verticeB->nombrev, verticeB->gradov);
    for(int i=0; i<gradoB; i++){
        printf("vecino %i : %lu\n", i, verticeB->vecinos[i]->nombrev);
    }

}


/*
Ejecucion de la carga de datos en un grafo g, apartir de un archivo de texto
pasado por consola.
*/
void run_parser(Grafo g){
    char path_name[100];
    printf("\n Indique ruta del archivo: \n");
    int scan_path_name = scanf("%s", path_name);
    printf("filename: %s\n", path_name);

    assert(scan_path_name > 0 && "Error al leer ruta del archivo");

    FILE *file = fopen(path_name, "r");
    assert(file != NULL && "Error al abrir archivo");
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
    char pseudo_edge[5]; // +1 por caracter de temrinación
    // si el primer caracter es EOF, no hay mas datos
    assert(firstchar == 'p' 
            && fscanf(file,"%s %lu %lu",pseudo_edge , &nver, &mlado) > 0
            && "Primer caracter no es 'p' o no formato (p edge n m)");
    assert(!strcmp("edge",pseudo_edge) && "no es edge, formato incorrecto");

    printf("%lu vertices y %lu Lados\n", nver, mlado);

    g->nver = nver;
    g->mlados = mlado;
    g->vertices = malloc(sizeof(Vertice) * nver);
    inicializarNullVertices(g);
    g->vertOrdNat = malloc(sizeof(Vertice) * nver);

    // lectura de los lados con vertices
    // formato de cada linea: e v1 v2
    u32 vA, vB;
    u32 count_m = 0;
    while(count_m <= mlado-1){
        /*
            cuando hacemos fscanf(file,"%s %lu %lu",pseudo_edge , &nver, &mlado)
            el siguiente fscanf tomara el salto de linea de la linea j-1
            y el siguiente fscanf sera el primer char de la linea j.
            no se como hacer para que lo ignore sin hacer que lo asigne a una 
            variable que no usaremos(lo probe con la var u32 vA y tampoco)
        */
        fscanf(file,"%c", &firstchar);
        u32 check_scan = fscanf(file,"%c", &firstchar);
        // estas al final de archivo o Error de lectura
        if (check_scan == EOF){
            printf("liberar memoria, retornar NULL 1\n");
            exit(EXIT_FAILURE);
        }
        // la linea cumple el formato: e v w 
        else if (firstchar == 'e' && fscanf(file,"%lu %lu", &vA, &vB) > 0){
            // ...
            // ... code here
            // ...
            // retorna puntero al vertice creado o encontrado
            Vertice verticeA = buscarVertice(g, vA);
            Vertice verticeB = buscarVertice(g, vB);
            //agregar vertice como vecino de otro y viceversa.
            emparejarVertices(verticeA, verticeB);

            // chequear el nuevo grado del grafo

            printf("%lu %lu\n", vA, vB);
            count_m++;
            //g->mlados++;
        }
        // la linea no lo cumple 
        else{
            printf("liberar memoria, retornar NULL 2\n");
            exit(EXIT_FAILURE);
        }
    }

    //if (g->mlados < m)
}
/*
c
c
c
c
p
e
e
e
e
*/