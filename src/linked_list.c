#include "linked_list.h"
#include <stdlib.h>

// inicializa la lista poniendola vacia
void inicializar_lista(lista_enlazada* lista) {
    lista->cabeza = NULL;
}

// verifica si la lista esta vacia
bool esta_lista_vacia(lista_enlazada* lista) {
    return lista->cabeza == NULL;
}

// inserta un proceso en la lista manteniendo el orden por su pid
void insertar_ordenado_por_pid(lista_enlazada* lista, proceso p) {
    lista_nodos* nuevo_nodo = (lista_nodos*)malloc(sizeof(lista_nodos));
    if (!nuevo_nodo) return; // fallo de memoria
    
    nuevo_nodo->p = p;
    nuevo_nodo->siguiente = NULL;
    
    // si la lista esta vacia o el nuevo pid es menor que el de la cabeza
    if (esta_lista_vacia(lista) || lista->cabeza->p.pid >= p.pid) {
        nuevo_nodo->siguiente = lista->cabeza;
        lista->cabeza = nuevo_nodo;
        return;
    }
    
    // buscar la posicion correcta en el resto de la lista
    lista_nodos* actual = lista->cabeza;
    while (actual->siguiente != NULL && actual->siguiente->p.pid < p.pid) {
        actual = actual->siguiente;
    }
    
    // insertar el nuevo nodo despues de actual
    nuevo_nodo->siguiente = actual->siguiente;
    actual->siguiente = nuevo_nodo;
}
