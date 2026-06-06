#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "process.h"
#include <stdbool.h>

// nodo para la lista enlazada
typedef struct lista_nodos {
    Process p;
    struct lista_nodos* siguiente;
} lista_nodos;

// estructura principal para almacenar los procesos finalizados
typedef struct {
    lista_nodos* cabeza;
} lista_enlazada;

// inicializa la lista poniendola vacia
void inicializar_lista(lista_enlazada* lista);

// verifica si la lista esta vacia
bool esta_lista_vacia(lista_enlazada* lista);

// inserta un proceso en la lista manteniendo el orden por su pid
void insertar_ordenado_por_pid(lista_enlazada* lista, Process p);

#endif // LINKED_LIST_H
