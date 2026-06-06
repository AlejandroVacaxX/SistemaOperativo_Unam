#include "round_robin.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep((x) * 1000)
#else
#include <unistd.h>
#endif

//codito ANSI para colores de consola
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

// round robin
void ejecutar_round_robin(cola_circular* cc_listos, lista_enlazada* lista_finalizada, pila* historial, int quantum) {
    printf("\n--- Iniciando planificacion round robin [quantum: %d] ---\n", quantum);
    
    while (!cc_vacia(cc_listos)) {
        Process p = desencolar_cc(cc_listos);
        
        printf(GREEN "Ejecutando proceso %d" RESET ": tiempo restante %d\n", p.pid, p.remaining_time);
        //sleep(1); 
        
        // marcamos el proceso como en ejecucion
        p.state = RUNNING;
        apilar(historial, p);
        
        if (p.remaining_time > quantum) {
            // el proceso todavia necesita tiempo, lo interrumpimos y regresa a la cola
            p.remaining_time -= quantum;
            p.state = READY;
            printf(YELLOW "  Quantum expirado" RESET ". proceso %d reencolado con %d restante\n", p.pid, p.remaining_time);
            apilar(historial, p);
            encolar_cc(cc_listos, p);
        } else {
            // el proceso termina su trabajo dentro del quantum actual
            printf(RED "  * proceso %d termino su rafaga" RESET ". enviando a lista de finalizados\n", p.pid);
            p.remaining_time = 0;
            p.state = FINISHED;
            apilar(historial, p);
            insertar_ordenado_por_pid(lista_finalizada, p);
        }
        //sleep(1); 
    }
    printf("--- fin de round robin ---\n\n");
}
