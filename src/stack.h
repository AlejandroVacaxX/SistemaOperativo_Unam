#ifndef STACK_H
#define STACK_H

#include "process.h"
#include <stdbool.h>

#define MAX_STACK_SIZE 100

// estructura de pila para historial y backtracking
typedef struct {
    proceso elementos[MAX_STACK_SIZE];
    int tope;
} pila;

// inicializa la pila poniendola vacia
void inicializar_pila(pila* s);

// verifica si la pila esta vacia
bool esta_pila_vacia(pila* s);

// verifica si la pila alcanzo su limite
bool esta_pila_llena(pila* s);

// agrega un proceso a la pila
bool apilar(pila* s, proceso p);

// saca y retorna el proceso en el tope de la pila
proceso desapilar(pila* s);

#endif // STACK_H
