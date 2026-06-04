#include "csv_exporter.h"
#include <stdio.h>

// abrimos el archivo de salida y recorremos la lista de procesos terminados para guardar sus datos
void export_results_to_csv(const char* filename, linked_list* finished_list) {
    FILE* file = fopen(filename, "w");
    if (!file) return;

    // encabezados para el archivo de resultados
    fprintf(file, "pid,burst_time,priority,memory_required,state\n");

    list_node* current = finished_list->head;
    while (current != NULL) {
        process p = current->p;
        
        // convertimos el estado numerico a una etiqueta de texto legible
        char* state_str;
        switch (p.state) {
            case READY: state_str = "ready"; break;
            case RUNNING: state_str = "running"; break;
            case BLOCKED: state_str = "blocked"; break;
            case FINISHED: state_str = "finished"; break;
            default: state_str = "unknown"; break;
        }

        // escribimos los datos con el estado en formato de texto
        fprintf(file, "%d,%d,%d,%d,%s\n", 
                p.pid, p.burst_time, p.priority, p.memory_required, state_str);
        current = current->next;
    }

    fclose(file);
}
