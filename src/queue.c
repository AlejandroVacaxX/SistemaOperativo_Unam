#include "queue.h"
#include <stdlib.h>

// inicializa la cola poniendola vacia
void init_queue(queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

// verifica si la cola esta vacia
bool is_queue_empty(queue* q) {
    return q->front == NULL;
}

// encola un proceso al final de la cola
void enqueue(queue* q, process p) {
    queue_node* new_node = (queue_node*)malloc(sizeof(queue_node));
    if (!new_node) return; // fallo de asignacion de memoria
    
    new_node->p = p;
    new_node->next = NULL;
    
    if (is_queue_empty(q)) {
        q->front = new_node;
        q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}

// desencola y retorna el proceso al frente de la cola
process dequeue(queue* q) {
    process empty_p = {0};
    if (is_queue_empty(q)) {
        return empty_p;
    }
    
    queue_node* temp = q->front;
    process p = temp->p;
    
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    return p;
}
