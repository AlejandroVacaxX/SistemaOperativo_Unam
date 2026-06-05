#ifndef MEMORY_BLOCK_H
#define MEMORY_BLOCK_H

#include <stdbool.h>

// definicion del bloque de memoria como un nodo de una lista doblemente enlazada
typedef struct bloque_memoria {
    int inicio;
    int tamano;
    bool libre;
    int pid;
    struct bloque_memoria* siguiente;
    struct bloque_memoria* anterior;
} bloque_memoria;

#endif // MEMORY_BLOCK_H
