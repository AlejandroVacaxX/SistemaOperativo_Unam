#include "circular_queue.h"

// inicializa la cola circular poniendola vacia
void init_cq(circular_queue* cq) {
    cq->front = 0;
    cq->rear = -1;
    cq->count = 0;
}

// verifica si la cola circular esta vacia
bool is_cq_empty(circular_queue* cq) {
    return cq->count == 0;
}

// verifica si la cola circular alcanzo su limite de capacidad
bool is_cq_full(circular_queue* cq) {
    return cq->count == MAX_CQ_SIZE;
}

// encola un proceso en la cola circular
bool enqueue_cq(circular_queue* cq, process p) {
    if (is_cq_full(cq)) {
        return false;
    }
    
    cq->rear = (cq->rear + 1) % MAX_CQ_SIZE;
    cq->items[cq->rear] = p;
    cq->count++;
    
    return true;
}

// desencola y retorna el proceso al frente de la cola circular
process dequeue_cq(circular_queue* cq) {
    process p = {0}; // proceso vacio por defecto
    if (!is_cq_empty(cq)) {
        p = cq->items[cq->front];
        cq->front = (cq->front + 1) % MAX_CQ_SIZE;
        cq->count--;
    }
    return p;
}
