#include "linked_list.h"
#include <stdlib.h>

// inicializa la lista poniendola vacia
void init_list(linked_list* list) {
    list->head = NULL;
}

// verifica si la lista esta vacia
bool is_list_empty(linked_list* list) {
    return list->head == NULL;
}

// inserta un proceso en la lista manteniendo el orden por su pid
void insert_ordered_by_pid(linked_list* list, process p) {
    list_node* new_node = (list_node*)malloc(sizeof(list_node));
    if (!new_node) return; // fallo de memoria
    
    new_node->p = p;
    new_node->next = NULL;
    
    // si la lista esta vacia o el nuevo pid es menor que el de la cabeza
    if (is_list_empty(list) || list->head->p.pid >= p.pid) {
        new_node->next = list->head;
        list->head = new_node;
        return;
    }
    
    // buscar la posicion correcta en el resto de la lista
    list_node* current = list->head;
    while (current->next != NULL && current->next->p.pid < p.pid) {
        current = current->next;
    }
    
    // insertar el nuevo nodo despues de current
    new_node->next = current->next;
    current->next = new_node;
}
