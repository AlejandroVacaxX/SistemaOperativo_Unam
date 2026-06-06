#ifndef MEMORY_BLOCK_H
#define MEMORY_BLOCK_H

#include <stdbool.h>

// definicion del bloque de memoria como un nodo de una lista doblemente enlazada
typedef struct MemoryBlock {
    int start;
    int size;
    bool free;
    int pid;
    struct MemoryBlock* siguiente;
    struct MemoryBlock* anterior;
} MemoryBlock;

#endif 
