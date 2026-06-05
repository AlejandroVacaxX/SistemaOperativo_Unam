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
        proceso p = actual->p;
        
        // convertimos el estado numerico a una etiqueta de texto legible
        char* estado_str;
        switch (p.estado) {
            case LISTO: estado_str = "listo"; break;
            case EJECUCION: estado_str = "ejecucion"; break;
            case BLOQUEADO: estado_str = "bloqueado"; break;
            case FINALIZADO: estado_str = "finalizado"; break;
            default: estado_str = "desconocido"; break;
        }

        // escribimos los datos con el estado en formato de texto
        fprintf(file, "%d,%d,%d,%d,%s\n", 
                p.pid, p.tiempo_rafaga, p.prioridad, p.memoria_requerida, estado_str);
        actual = actual->siguiente;
    }

    fclose(file);
}
