#include "csv_parser.h"
#include "csv_exporter.h"
#include "fifo.h"
#include "round_robin.h"
#include "sjf.h"
#include <stdio.h>
#include <string.h>

#define MAX_PROCESSES 1000

// punto de entrada optimizado para ser llamado desde python sin interrupcion humana
int main(int argc, char* argv[]) {
    if (argc < 3) {
        return 1;
    }

    const char* algorithm = argv[1];
    const char* input_file = "input.csv";
    const char* output_file = "output.csv";

    process processes[MAX_PROCESSES];
    int count = load_processes_from_csv(input_file, processes, MAX_PROCESSES);
    
    if (count == 0) return 1;

    linked_list finished_list;
    init_list(&finished_list);
    
    stack history;
    init_stack(&history);

    // seleccionamos el algoritmo segun el argumento recibido desde el orquestador
    if (strcmp(algorithm, "fifo") == 0) {
        queue q;
        init_queue(&q);
        for (int i = 0; i < count; i++) enqueue(&q, processes[i]);
        run_fifo(&q, &finished_list, &history);
    } 
    else if (strcmp(algorithm, "rr") == 0) {
        circular_queue cq;
        init_cq(&cq);
        for (int i = 0; i < count; i++) enqueue_cq(&cq, processes[i]);
        run_round_robin(&cq, &finished_list, &history, 2); // quantum por defecto
    }
    else if (strcmp(algorithm, "sjf") == 0) {
        run_sjf(processes, count, &finished_list, &history);
    }

    export_results_to_csv(output_file, &finished_list);

    return 0;
}
