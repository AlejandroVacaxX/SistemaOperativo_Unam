#include "csv_parser.h"
#include "csv_exporter.h"
#include "fifo.h"
#include "round_robin.h"
#include "sjf.h"
#include "memory_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define RESET_COLOR "\033[0m"

#define MAX_PROCESSES 1000

// punto de entrada optimizado para ser llamado desde python 
int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }

    const char* algorithm = argv[1];
    const char* input_file = "input.csv";
    const char* output_file = "output.csv";

    // ejecutamos una simulacion visual de la ram
    if (strcmp(algorithm, "demo_memoria") == 0) {
        printf("\n--- iniciando demostracion visual de gestion de memoria ---\n");
        memory_block* ram = init_memory(500);
        printf("memoria inicializada con 500 unidades\n");
        print_memory_map(ram);
        sleep(1);

        printf("\nasignando memoria para p1[100], p2[150] y p3[50] \n");
        allocate_memory(ram, 1, 100, FIRST_FIT);
        allocate_memory(ram, 2, 150, FIRST_FIT);
        allocate_memory(ram, 3, 50, FIRST_FIT);
        print_memory_map(ram);
        sleep(1);
        
        printf("\nliberando p2 y p3 para crear bloques libres contiguos...\n");
        memory_block* curr = ram;
        while(curr) {
            if(curr->pid == 2 || curr->pid == 3) {
                deallocate_memory(curr);
            }
            curr = curr->next;
        }
        print_memory_map(ram);
        sleep(1);
        
        printf("\n ejecutando coalescencia para unir bloques libres...\n");
        coalesce_memory(ram);
        print_memory_map(ram);
        sleep(1);
        
        printf("\n--- fin de demostracion de memoria ---\n\n");
        
        // limpieza de memoria
        free_memory_list(ram);
        return 0;
    }

    process processes[MAX_PROCESSES];
    int count = load_processes_from_csv(input_file, processes, MAX_PROCESSES);
    
    if (count == 0) return 1;

    linked_list finished_list;
    init_list(&finished_list);
    
    stack history;
    init_stack(&history);

    if (strcmp(algorithm, "fifo") == 0) {
        cola q;
        iniciar_cola(&q);
        for (int i = 0; i < count; i++) encolar(&q, processes[i]);
        run_fifo(&q, &finished_list, &history);
    } 
    else if (strcmp(algorithm, "rr") == 0) {
        cola_circular cq;
        iniciar_cc(&cq);
        for (int i = 0; i < count; i++) encolar_cc(&cq, processes[i]);
        run_round_robin(&cq, &finished_list, &history, 2);
    }
    else if (strcmp(algorithm, "sjf") == 0) {
        run_sjf(processes, count, &finished_list, &history);
    }

    export_results_to_csv(output_file, &finished_list);

    return 0;
}
