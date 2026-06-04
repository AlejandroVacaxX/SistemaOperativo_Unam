#ifndef CSV_EXPORTER_H
#define CSV_EXPORTER_H

#include "linked_list.h"

// guarda los procesos finalizados y sus metricas en un archivo csv
void export_results_to_csv(const char* filename, linked_list* finished_list);

#endif // CSV_EXPORTER_H
