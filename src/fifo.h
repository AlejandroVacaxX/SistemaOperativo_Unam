#ifndef FIFO_H
#define FIFO_H

#include "cola.h"
#include "linked_list.h"
#include "stack.h"

// ejecuta el planificador fifo procesando todos los procesos en la cola de listos
void ejecutar_fifo(cola* cola_listos, lista_enlazada* lista_finalizada, pila* historial);

#endif // FIFO_H
