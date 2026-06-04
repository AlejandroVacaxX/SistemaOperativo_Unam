#ifndef STACK_H
#define STACK_H

#include "process.h"
#include <stdbool.h>

#define MAX_STACK_SIZE 100

// estructura de pila para historial y backtracking
typedef struct {
    process items[MAX_STACK_SIZE];
    int top;
} stack;

// inicializa la pila poniendola vacia
void init_stack(stack* s);

// verifica si la pila esta vacia
bool is_stack_empty(stack* s);

// verifica si la pila alcanzo su limite
bool is_stack_full(stack* s);

// agrega un proceso a la pila
bool push(stack* s, process p);

// saca y retorna el proceso en el tope de la pila
process pop(stack* s);

#endif // STACK_H
