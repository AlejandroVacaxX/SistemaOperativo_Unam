#include "stack.h"

// inicializa la pila poniendola vacia
void inicializar_pila(pila* s) {
    s->tope = -1;
}

// verifica si la pila esta vacia
bool esta_pila_vacia(pila* s) {
    return s->tope == -1;
}

// verifica si la pila alcanzo su limite
bool esta_pila_llena(pila* s) {
    return s->tope == MAX_STACK_SIZE - 1;
}

// agrega un proceso a la pila si hay espacio
bool apilar(pila* s, Process p) {
    if (esta_pila_llena(s)) {
        return false;
    }
    s->elementos[++(s->tope)] = p;
    return true;
}

// saca y retorna el proceso en el tope de la pila
Process desapilar(pila* s) {
    Process p = {0}; // proceso vacio por defecto
    if (!esta_pila_vacia(s)) {
        p = s->elementos[(s->tope)--];
    }
    return p;
}
