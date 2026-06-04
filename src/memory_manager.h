#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "memory_block.h"

// inicializa la memoria principal con un unico bloque vacio del tamaño total
memory_block* init_memory(int total_size);

// intenta asignar un bloque de memoria para un proceso especifico
// usa una estrategia basica de busqueda de primer hueco (first fit)
memory_block* allocate_memory(memory_block* head, int pid, int size);

// libera un bloque de memoria asociado a un proceso
void deallocate_memory(memory_block* block);

#endif // MEMORY_MANAGER_H
