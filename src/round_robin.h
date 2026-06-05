#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "cola_circular.h"
#include "linked_list.h"
#include "stack.h"

// ejecuta el planificador round robin usando un quantum determinado para la interrupcion
void ejecutar_round_robin(cola_circular* cc_listos, lista_enlazada* lista_finalizada, pila* historial, int quantum);

#endif // ROUND_ROBIN_H
