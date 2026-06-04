#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "process.h"
#include <stdbool.h>

// nodo para la lista enlazada
typedef struct list_node {
    process p;
    struct list_node* next;
} list_node;

// estructura principal para almacenar los procesos finalizados
typedef struct {
    list_node* head;
} linked_list;

// inicializa la lista poniendola vacia
void init_list(linked_list* list);

// verifica si la lista esta vacia
bool is_list_empty(linked_list* list);

// inserta un proceso en la lista manteniendo el orden por su pid
void insert_ordered_by_pid(linked_list* list, process p);

#endif // LINKED_LIST_H
