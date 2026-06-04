#include "csv_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// abrimos el archivo y procesamos cada linea para extraer los atributos de los procesos
int load_processes_from_csv(const char* filename, process processes[], int max_processes) {
    FILE* file = fopen(filename, "r");
    if (!file) return 0;

    char line[256];
    int count = 0;

    // saltamos la primera linea que contiene los encabezados de las columnas
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return 0;
    }

    // leemos linea por linea hasta el final del archivo o alcanzar el limite maximo
    while (fgets(line, sizeof(line), file) && count < max_processes) {
        char* token = strtok(line, ",");
        if (token) processes[count].pid = atoi(token);

        token = strtok(NULL, ",");
        if (token) {
            processes[count].burst_time = atoi(token);
            processes[count].remaining_time = processes[count].burst_time;
        }

        token = strtok(NULL, ",");
        if (token) processes[count].priority = atoi(token);

        token = strtok(NULL, ",");
        if (token) processes[count].memory_required = atoi(token);

        processes[count].state = READY;
        count++;
    }

    fclose(file);
    return count;
}
