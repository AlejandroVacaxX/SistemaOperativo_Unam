#include "stack.h"

// inicializa la pila poniendola vacia
void init_stack(stack* s) {
    s->top = -1;
}

// verifica si la pila esta vacia
bool is_stack_empty(stack* s) {
    return s->top == -1;
}

// verifica si la pila alcanzo su limite
bool is_stack_full(stack* s) {
    return s->top == MAX_STACK_SIZE - 1;
}

// agrega un proceso a la pila si hay espacio
bool push(stack* s, process p) {
    if (is_stack_full(s)) {
        return false;
    }
    s->items[++(s->top)] = p;
    return true;
}

// saca y retorna el proceso en el tope de la pila
process pop(stack* s) {
    process p = {0}; // proceso vacio por defecto
    if (!is_stack_empty(s)) {
        p = s->items[(s->top)--];
    }
    return p;
}
