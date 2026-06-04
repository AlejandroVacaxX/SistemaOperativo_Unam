#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "process.h"
#include <stdbool.h>

#define MAX_CQ_SIZE 100

// estructura de cola circular para el planificador round robin
typedef struct {
    process items[MAX_CQ_SIZE];
    int front;
    int rear;
    int count;
} circular_queue;

// inicializa la cola circular poniendola vacia
void init_cq(circular_queue* cq);

// verifica si la cola circular esta vacia
bool is_cq_empty(circular_queue* cq);

// verifica si la cola circular alcanzo su limite de capacidad
bool is_cq_full(circular_queue* cq);

// encola un proceso en la cola circular
bool enqueue_cq(circular_queue* cq, process p);

// desencola y retorna el proceso al frente de la cola circular
process dequeue_cq(circular_queue* cq);

#endif // CIRCULAR_QUEUE_H
