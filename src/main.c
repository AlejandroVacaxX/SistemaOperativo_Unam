#include "csv_parser.h"
#include "csv_exporter.h"
#include "fifo.h"
#include "round_robin.h"
#include "sjf.h"
#include "memory_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep((x) * 1000)
#else
#include <unistd.h>
#endif

#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define RESET_COLOR "\033[0m"

#define MAX_PROCESSES 1000

// punto de entrada optimizado para ser llamado desde python 
int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }

    const char* algoritmo = argv[1];
    const char* archivo_entrada = "input.csv";
    const char* archivo_salida = "output.csv";

    // ejecutamos una simulacion visual de la ram
    if (strcmp(algoritmo, "demo_memoria") == 0) {
        printf("\n--- iniciando demostracion visual de gestion de memoria ---\n");
        MemoryBlock* memoria = inicializar_memoria(500);
        printf("memoria inicializada con 500 unidades\n");
        imprimir_mapa_memoria(memoria);
        //sleep(1);

        printf("\nasignando memoria para p1[100], p2[150] y p3[50] \n");
        asignar_memoria(memoria, 1, 100, FIRST_FIT);
        asignar_memoria(memoria, 2, 150, FIRST_FIT);
        asignar_memoria(memoria, 3, 50, FIRST_FIT);
        imprimir_mapa_memoria(memoria);
        //sleep(1);
        
        printf("\n liberando p2 y p3 para crear bloques libres contiguos \n");
        MemoryBlock* actual = memoria;
        while(actual) {
            if(actual->pid == 2 || actual->pid == 3) {
                liberar_memoria(actual);
            }
            actual = actual->siguiente;
        }
        imprimir_mapa_memoria(memoria);
        //sleep(1);
        
        printf("\n ejecutando coalescencia para unir bloques libres \n");
        unir_memoria(memoria);
        imprimir_mapa_memoria(memoria);
        //sleep(1);
        
        printf("\n--- fin de demostracion de memoria ---\n\n");
        
        
        liberar_lista_memoria(memoria);
        return 0;
    }

    Process procesos[MAX_PROCESSES];
    int cantidad = cargar_procesos_desde_csv(archivo_entrada, procesos, MAX_PROCESSES);
    
    if (cantidad == 0) return 1;

    lista_enlazada lista_finalizada;
    inicializar_lista(&lista_finalizada);
    
    pila historial;
    inicializar_pila(&historial);

    if (strcmp(algoritmo, "fifo") == 0) {
        cola q;
        iniciar_cola(&q);
        for (int i = 0; i < cantidad; i++) encolar(&q, procesos[i]);
        ejecutar_fifo(&q, &lista_finalizada, &historial);
    } 
    else if (strcmp(algoritmo, "rr") == 0) {
        cola_circular cq;
        iniciar_cc(&cq);
        for (int i = 0; i < cantidad; i++) encolar_cc(&cq, procesos[i]);
        ejecutar_round_robin(&cq, &lista_finalizada, &historial, 2);
    }
    else if (strcmp(algoritmo, "sjf") == 0) {
        ejecutar_sjf(procesos, cantidad, &lista_finalizada, &historial);
    }

    exportar_dato_csv(archivo_salida, &lista_finalizada);

    return 0;
}
