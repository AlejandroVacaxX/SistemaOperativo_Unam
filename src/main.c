#include "csv_parser.h"
#include "csv_exporter.h"
#include "fifo.h"
#include <stdio.h>

#define MAX_PROCESSES 100

// programa principal que integra la lectura, simulacion y exportacion de resultados
int main() {
    process processes[MAX_PROCESSES];
    int count = load_processes_from_csv("input.csv", processes, MAX_PROCESSES);
    
    if (count == 0) {
        // no se pudieron cargar procesos, terminamos temprano
        return 1;
    }

    queue ready_queue;
    init_queue(&ready_queue);
    
    linked_list finished_list;
    init_list(&finished_list);
    
    stack history;
    init_stack(&history);

    // cargamos los procesos leidos en la cola de listos para el planificador
    for (int i = 0; i < count; i++) {
        enqueue(&ready_queue, processes[i]);
    }

    // ejecutamos la simulacion con el algoritmo fifo como prueba inicial
    run_fifo(&ready_queue, &finished_list, &history);

    // guardamos los resultados finales para que python los analice
    export_results_to_csv("output.csv", &finished_list);

    return 0;
}
