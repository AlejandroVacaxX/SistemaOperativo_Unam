#include "csv_exporter.h"
#include <stdio.h>

// abrimos el archivo de salida y recorremos la lista de procesos terminados para guardar sus datos
void exportar_dato_csv(const char* nombre_archivo, lista_enlazada* lista_finalizada) {
    FILE* file = fopen(nombre_archivo, "w");
    if (!file) return;

    // encabezados para el archivo de resultados
    fprintf(file, "pid,tiempo_rafaga,prioridad,memoria_requerida,estado\n");

    lista_nodos* actual = lista_finalizada->cabeza;
    while (actual != NULL) {
        Process p = actual->p;
        
        // convertimos el estado numerico a una etiqueta de texto legible
        char* estado_str;
        switch (p.state) {
            case READY: estado_str = "listo"; break;
            case RUNNING: estado_str = "ejecucion"; break;
            case BLOCKED: estado_str = "bloqueado"; break;
            case FINISHED: estado_str = "finalizado"; break;
            default: estado_str = "desconocido"; break;
        }

        // escribimos los datos con el estado en formato de texto
        fprintf(file, "%d,%d,%d,%d,%s\n", 
                p.pid, p.burst_time, p.priority, p.memory_required, estado_str);
        actual = actual->siguiente;
    }

    fclose(file);
}
