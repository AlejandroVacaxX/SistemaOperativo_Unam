#ifndef COLA_H
#define COLA_H

#include "process.h"
#include <stdbool.h>

// nodo individual para la cola dinamica
typedef struct nodo_cola {
    Process p;
    struct nodo_cola* siguiente;
} nodo_cola;

// estructura de la cola para los planificadores como fifo
typedef struct {
    nodo_cola* frente;
    nodo_cola* final;
} cola;

// inicializa la cola poniendola vacia
void iniciar_cola(cola* c);

// verifica si la cola esta vacia
bool cola_vacia(cola* c);

// encola un proceso al final de la cola
void encolar(cola* c, Process p);

// desencola y retorna el proceso al frente de la cola
Process desencolar(cola* c);

#endif // COLA_H
