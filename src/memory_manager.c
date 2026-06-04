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

// buscamos el primer bloque libre que tenga espacio suficiente para el proceso
memory_block* allocate_memory(memory_block* head, int pid, int size) {
    memory_block* current = head;
    
    while (current != NULL) {
        if (current->free && current->size >= size) {
            // si el bloque es mas grande de lo necesario lo dividimos
            if (current->size > size) {
                memory_block* new_block = (memory_block*)malloc(sizeof(memory_block));
                if (!new_block) return NULL;
                
                new_block->start = current->start + size;
                new_block->size = current->size - size;
                new_block->free = true;
                new_block->pid = -1;
                new_block->next = current->next;
                new_block->prev = current;
                
                if (current->next != NULL) {
                    current->next->prev = new_block;
                }
                
                current->next = new_block;
                current->size = size;
            }
            
            // ocupamos el bloque con la informacion del proceso
            current->free = false;
            current->pid = pid;
            return current;
        }
        current = current->next;
    }
    
    return NULL; // no se encontro espacio suficiente
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
