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
        // escribimos los datos basicos del proceso que ya termino su ejecucion
        fprintf(file, "%d,%d,%d,%d,%d\n", 
                p.pid, p.burst_time, p.priority, p.memory_required, p.state);
        current = current->next;
    }

    fclose(file);
}
