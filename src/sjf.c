#include "sjf.h"
#include <stdbool.h>

// el algoritmo sjf aplica una estrategia codiciosa para elegir el proceso con menor tiempo de rafaga
void run_sjf(process processes[], int n, linked_list* finished_list, stack* history) {
    bool completed[n];
    for (int i = 0; i < n; i++) {
        completed[i] = false;
    }
    
    int completed_count = 0;
    while (completed_count < n) {
        int shortest_idx = -1;
        int min_burst = 2147483647; // maximo valor entero para comparar
        
        // buscamos el proceso que no ha terminado con la rafaga mas pequeña
        for (int i = 0; i < n; i++) {
            if (!completed[i] && processes[i].burst_time < min_burst) {
                min_burst = processes[i].burst_time;
                shortest_idx = i;
            }
        }
        
        if (shortest_idx != -1) {
            process* p = &processes[shortest_idx];
            
            // simulamos el cambio de estado a ejecucion
            p->state = RUNNING;
            push(history, *p);
            
            // en sjf no apropiativo el proceso corre hasta terminar
            p->remaining_time = 0;
            p->state = FINISHED;
            
            // registramos el final y lo pasamos a la lista de procesos terminados
            push(history, *p);
            insert_ordered_by_pid(finished_list, *p);
            
            completed[shortest_idx] = true;
            completed_count++;
        }
    }
}
