#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include "process.h"

// lee los procesos desde un archivo csv y los guarda en un arreglo
// devuelve la cantidad de procesos leidos exitosamente
int cargar_procesos_desde_csv(const char* nombre_archivo, Process procesos[], int procesos_maximos);

#endif // CSV_PARSER_H
