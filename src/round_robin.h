#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "cola_circular.h"
#include "linked_list.h"
#include "stack.h"

// ejecuta el planificador round robin usando un quantum determinado para la interrupcion
void run_round_robin(cola_circular* cc_listos, linked_list* finished_list, stack* history, int quantum);

#endif // ROUND_ROBIN_H
