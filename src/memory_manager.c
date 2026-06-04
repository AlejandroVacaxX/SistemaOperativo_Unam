#include "memory_manager.h"
#include <stdlib.h>

// creamos el primer bloque que representa toda la memoria disponible al inicio
memory_block* init_memory(int total_size) {
    memory_block* head = (memory_block*)malloc(sizeof(memory_block));
    if (!head) return NULL;
    
    head->start = 0;
    head->size = total_size;
    head->free = true;
    head->pid = -1;
    head->next = NULL;
    head->prev = NULL;
    
    return head;
}

// funcion auxiliar para dividir un bloque si es mas grande de lo necesario
void split_block(memory_block* block, int size) {
    if (block->size > size) {
        memory_block* new_block = (memory_block*)malloc(sizeof(memory_block));
        if (!new_block) return;
        
        new_block->start = block->start + size;
        new_block->size = block->size - size;
        new_block->free = true;
        new_block->pid = -1;
        new_block->next = block->next;
        new_block->prev = block;
        
        if (block->next != NULL) {
            block->next->prev = new_block;
        }
        
        block->next = new_block;
        block->size = size;
    }
}

// buscamos el primer bloque libre que tenga espacio suficiente (estrategia rapida)
memory_block* find_first_fit(memory_block* head, int size) {
    memory_block* current = head;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// buscamos el bloque libre mas pequeño que sea suficiente (estrategia para reducir desperdicio)
memory_block* find_best_fit(memory_block* head, int size) {
    memory_block* current = head;
    memory_block* best = NULL;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            if (best == NULL || current->size < best->size) {
                best = current;
            }
        }
        current = current->next;
    }
    return best;
}

// buscamos el bloque libre mas grande disponible (estrategia para dejar huecos grandes)
memory_block* find_worst_fit(memory_block* head, int size) {
    memory_block* current = head;
    memory_block* worst = NULL;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            if (worst == NULL || current->size > worst->size) {
                worst = current;
            }
        }
        current = current->next;
    }
    return worst;
}

// funcion principal de asignacion que delega segun la estrategia elegida
memory_block* allocate_memory(memory_block* head, int pid, int size, allocation_strategy strategy) {
    memory_block* target = NULL;
    
    switch (strategy) {
        case FIRST_FIT:
            target = find_first_fit(head, size);
            break;
        case BEST_FIT:
            target = find_best_fit(head, size);
            break;
        case WORST_FIT:
            target = find_worst_fit(head, size);
            break;
    }
    
    if (target != NULL) {
        split_block(target, size);
        target->free = false;
        target->pid = pid;
    }
    
    return target;
}

// simplemente marcamos el bloque como libre para que pueda ser reusado
void deallocate_memory(memory_block* block) {
    if (block != NULL) {
        block->free = true;
        block->pid = -1;
    }
}

// recorremos la lista sumando el tamaño de todos los bloques que estan marcados como libres
int get_total_free_memory(memory_block* head) {
    int total = 0;
    memory_block* current = head;
    while (current != NULL) {
        if (current->free) {
            total += current->size;
        }
        current = current->next;
    }
    return total;
}

// un hueco es un bloque libre; contamos cuantos de estos hay dispersos por la lista
int count_memory_holes(memory_block* head) {
    int holes = 0;
    memory_block* current = head;
    while (current != NULL) {
        if (current->free) {
            holes++;
        }
        current = current->next;
    }
    return holes;
}

// buscamos entre todos los bloques libres cual es el que tiene la mayor capacidad
int get_largest_hole_size(memory_block* head) {
    int max_size = 0;
    memory_block* current = head;
    while (current != NULL) {
        if (current->free && current->size > max_size) {
            max_size = current->size;
        }
        current = current->next;
    }
    return max_size;
}

// buscamos parejas de bloques libres contiguos para unificarlos en uno solo
void coalesce_memory(memory_block* head) {
    memory_block* current = head;
    while (current != NULL && current->next != NULL) {
        if (current->free && current->next->free) {
            memory_block* next_block = current->next;
            current->size += next_block->size;
            current->next = next_block->next;
            if (next_block->next != NULL) {
                next_block->next->prev = current;
            }
            free(next_block);
        } else {
            current = current->next;
        }
    }
}

// buscamos en cada bloque de la lista sin saltarnos ninguno para ver si cabe el proceso
void find_all_holes_brute_force(memory_block* head, int size) {
    memory_block* current = head;
    int found_count = 0;
    
    while (current != NULL) {
        if (current->free && current->size >= size) {
            found_count++;
            // aqui simplemente imprimimos la informacion del hueco encontrado
            // en una aplicacion real podriamos devolver una lista de punteros
        }
        current = current->next;
    }
}
