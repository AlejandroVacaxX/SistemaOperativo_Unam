#include "cola.h"
#include <stdlib.h>

// inicializa la cola poniendola vacia
void iniciar_cola(cola* c) {
    c->frente = NULL;
    c->final = NULL;
}

// verifica si la cola esta vacia
bool cola_vacia(cola* c) {
    return c->frente == NULL;
}

// encola un proceso al final de la cola
void encolar(cola* c, Process p) {
    nodo_cola* nuevo_nodo = (nodo_cola*)malloc(sizeof(nodo_cola));
    if (!nuevo_nodo) return; // fallo de asignacion de memoria
    
    nuevo_nodo->p = p;
    nuevo_nodo->siguiente = NULL;
    
    if (cola_vacia(c)) {
        c->frente = nuevo_nodo;
        c->final = nuevo_nodo;
    } else {
        c->final->siguiente = nuevo_nodo;
        c->final = nuevo_nodo;
    }
}

// desencola y retorna el proceso al frente de la cola
Process desencolar(cola* c) {
    Process p_vacio = {0};
    if (cola_vacia(c)) {
        return p_vacio;
    }
    
    nodo_cola* temporal = c->frente;
    Process p = temporal->p;
    
    c->frente = c->frente->siguiente;
    
    if (c->frente == NULL) {
        c->final = NULL;
    }
    
    free(temporal);
    return p;
}
