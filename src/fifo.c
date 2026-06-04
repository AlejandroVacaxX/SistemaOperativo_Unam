#include "fifo.h"
#include <stdio.h>

// el algoritmo fifo procesa los procesos en el orden exacto en que llegaron a la cola
void run_fifo(cola* cola_listos, linked_list* finished_list, stack* history) {
    while (!cola_vacia(cola_listos)) {
        process p = desencolar(cola_listos);
        
        // cambiamos el estado a ejecutandose para iniciar la simulacion
        p.state = RUNNING;
        push(history, p);
        
        // en fifo el proceso corre hasta terminar sin interrupciones
        p.remaining_time = 0;
        p.state = FINISHED;
        
        // registramos el fin del proceso y lo guardamos en la lista de terminados
        push(history, p);
        insert_ordered_by_pid(finished_list, p);
    }
}
