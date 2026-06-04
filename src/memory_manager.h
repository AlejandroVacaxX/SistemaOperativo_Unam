#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "memory_block.h"

typedef enum {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
} allocation_strategy;

// inicializa la memoria principal con un unico bloque vacio del tamaño total
memory_block* init_memory(int total_size);

// intenta asignar un bloque de memoria para un proceso especifico usando una estrategia
memory_block* allocate_memory(memory_block* head, int pid, int size, allocation_strategy strategy);

// libera un bloque de memoria asociado a un proceso
void deallocate_memory(memory_block* block);

// calcula la cantidad total de memoria libre en el sistema
int get_total_free_memory(memory_block* head);

// cuenta cuantos huecos (bloques libres separados) existen actualmente
int count_memory_holes(memory_block* head);

// determina el tamaño del hueco mas grande disponible
int get_largest_hole_size(memory_block* head);

// recorre la lista de memoria uniendo bloques libres que esten uno junto al otro
void coalesce_memory(memory_block* head);

// busca exhaustivamente todos los huecos que pueden contener un tamaño especifico
// imprime la ubicacion y tamaño de cada hueco encontrado
void find_all_holes_brute_force(memory_block* head, int size);

#endif // MEMORY_MANAGER_H
