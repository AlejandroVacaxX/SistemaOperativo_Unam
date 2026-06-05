#ifndef CSV_EXPORTER_H
#define CSV_EXPORTER_H

#include "linked_list.h"

// guarda los procesos finalizados y sus metricas en un archivo csv
void exportar_dato_csv(const char* nombre_archivo, lista_enlazada* lista_finalizada);

#endif // CSV_EXPORTER_H
