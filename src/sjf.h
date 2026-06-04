#ifndef SJF_H
#define SJF_H

#include "process.h"
#include "linked_list.h"
#include "stack.h"

// ejecuta el planificador shortest job first seleccionando el proceso mas corto
void run_sjf(process processes[], int n, linked_list* finished_list, stack* history);

#endif // SJF_H
