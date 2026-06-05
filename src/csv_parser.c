#include "csv_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// abrimos el archivo y procesamos cada linea para extraer los atributos de los procesos
int cargar_procesos_desde_csv(const char* nombre_archivo, proceso procesos[], int procesos_maximos) {
    FILE* file = fopen(nombre_archivo, "r");
    if (!file) return 0;

    char line[256];
    int count = 0;

    // saltamos la primera linea que contiene los encabezados de las columnas
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return 0;
    }

    // leemos linea por linea hasta el final del archivo o alcanzar el limite maximo
    while (fgets(line, sizeof(line), file) && count < procesos_maximos) {
        char* token = strtok(line, ",");
        if (token) procesos[count].pid = atoi(token);

        token = strtok(NULL, ",");
        if (token) {
            procesos[count].tiempo_rafaga = atoi(token);
            procesos[count].tiempo_restante = procesos[count].tiempo_rafaga;
        }

        token = strtok(NULL, ",");
        if (token) procesos[count].prioridad = atoi(token);

        token = strtok(NULL, ",");
        if (token) procesos[count].memoria_requerida = atoi(token);

        procesos[count].estado = LISTO;
        count++;
    }

    fclose(file);
    return count;
}
