#include "csv_exporter.h"
#include <stdio.h>

// abrimos el archivo de salida y recorremos la lista de procesos terminados para guardar sus datos
void exportar_dato_csv(const char* nombre_archivo, lista_enlazada* lista_finalizada) {
    FILE* file = fopen(nombre_archivo, "w");
    if (!file) return;

    // encabezados para el archivo de resultados
    fprintf(file, "pid,burst_time,priority,memory_required,state\n");

    lista_nodos* actual = lista_finalizada->cabeza;
    while (actual != NULL) {
        Process p = actual->p;
        
        // convertimos el estado numerico a una etiqueta de texto legible
        char* estado_str;
        switch (p.state) {
            case READY: estado_str = "ready"; break;
            case RUNNING: estado_str = "running"; break;
            case BLOCKED: estado_str = "blocked"; break;
            case FINISHED: estado_str = "finished"; break;
            default: estado_str = "unknown"; break;
        }

        // escribimos los datos con el estado en formato de texto
        fprintf(file, "%d,%d,%d,%d,%s\n", 
                p.pid, p.burst_time, p.priority, p.memory_required, estado_str);
        actual = actual->siguiente;
    }

    fclose(file);
}
