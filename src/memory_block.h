#ifndef MEMORY_BLOCK_H
#define MEMORY_BLOCK_H

#include <stdbool.h>

// definicion del bloque de memoria como un nodo de una lista doblemente enlazada
typedef struct memory_block {
    int start;
    int size;
    bool free;
    int pid;
    struct memory_block* next;
    struct memory_block* prev;
} memory_block;

#endif // MEMORY_BLOCK_H
