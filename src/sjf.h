#ifndef SJF_H
#define SJF_H

#include "process.h"
#include "linked_list.h"
#include "stack.h"

// ejecuta el planificador shortest job first seleccionando el proceso mas corto
void ejecutar_sjf(proceso procesos[], int n, lista_enlazada* lista_finalizada, pila* historial);

#endif // SJF_H
