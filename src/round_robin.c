#include "round_robin.h"
#include <stdio.h>
#include <unistd.h> // necesario para la funcion sleep en sistemas unix

// codigos de escape ansi para darle color a la consola
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

// el algoritmo round robin reparte el tiempo de cpu equitativamente usando un quantum
void run_round_robin(circular_queue* ready_cq, linked_list* finished_list, stack* history, int quantum) {
    printf("\n--- iniciando planificacion round robin (quantum: %d) ---\n", quantum);
    
    while (!is_cq_empty(ready_cq)) {
        process p = dequeue_cq(ready_cq);
        
        printf(GREEN "ejecutando proceso %d" RESET ": tiempo restante %d\n", p.pid, p.remaining_time);
        sleep(1); // pausa para poder seguir la ejecucion visualmente
        
        // marcamos el proceso como en ejecucion
        p.state = RUNNING;
        push(history, p);
        
        if (p.remaining_time > quantum) {
            // el proceso todavia necesita tiempo, lo interrumpimos y regresa a la cola
            p.remaining_time -= quantum;
            p.state = READY;
            printf(YELLOW "  ! quantum expirado" RESET ". proceso %d reencolado con %d restante\n", p.pid, p.remaining_time);
            push(history, p);
            enqueue_cq(ready_cq, p);
        } else {
            // el proceso termina su trabajo dentro del quantum actual
            printf(RED "  * proceso %d termino su rafaga" RESET ". enviando a lista de finalizados\n", p.pid);
            p.remaining_time = 0;
            p.state = FINISHED;
            push(history, p);
            insert_ordered_by_pid(finished_list, p);
        }
        sleep(1); // pausa entre turnos de procesos
    }
    printf("--- fin de la planificacion round robin ---\n\n");
}
