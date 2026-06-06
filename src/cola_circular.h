#ifndef COLA_CIRCULAR_H
#define COLA_CIRCULAR_H

#include "process.h"
#include <stdbool.h>

#define MAX_CC_TAMAÑO 100

// estructura de cola circular para el planificador round robin
typedef struct {
    Process elementos[MAX_CC_TAMAÑO];
    int frente;
    int final;
    int contador;
} cola_circular;

// inicializa la cola circular poniendola vacia
void iniciar_cc(cola_circular* cc);

// verifica si la cola circular esta vacia
bool cc_vacia(cola_circular* cc);

// verifica si la cola circular alcanzo su limite de capacidad
bool cc_llena(cola_circular* cc);

// encola un proceso en la cola circular
bool encolar_cc(cola_circular* cc, Process p);

// desencola y retorna el proceso al frente de la cola circular
Process desencolar_cc(cola_circular* cc);

#endif // COLA_CIRCULAR_H
