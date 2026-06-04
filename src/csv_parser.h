#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include "process.h"

// lee los procesos desde un archivo csv y los guarda en un arreglo
// devuelve la cantidad de procesos leidos exitosamente
int load_processes_from_csv(const char* filename, process processes[], int max_processes);

#endif // CSV_PARSER_H
