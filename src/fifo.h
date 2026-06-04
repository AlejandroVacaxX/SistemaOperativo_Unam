#ifndef FIFO_H
#define FIFO_H

#include "queue.h"
#include "linked_list.h"
#include "stack.h"

// ejecuta el planificador fifo procesando todos los procesos en la cola de listos
void run_fifo(queue* ready_queue, linked_list* finished_list, stack* history);

#endif // FIFO_H
