#ifndef QUEUE_H
#define QUEUE_H

#include "process.h"
#include <stdbool.h>

// nodo individual para la cola dinamica
typedef struct queue_node {
    process p;
    struct queue_node* next;
} queue_node;

// estructura de la cola para los planificadores como fifo
typedef struct {
    queue_node* front;
    queue_node* rear;
} queue;

// inicializa la cola poniendola vacia
void init_queue(queue* q);

// verifica si la cola esta vacia
bool is_queue_empty(queue* q);

// encola un proceso al final de la cola
void enqueue(queue* q, process p);

// desencola y retorna el proceso al frente de la cola
// precondicion: no debe llamarse si la cola esta vacia
process dequeue(queue* q);

#endif // QUEUE_H
