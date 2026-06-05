#include "round_robin.h"
#include <stdio.h>
#include <unistd.h> // biblioteca para sleep en unix

//codito ANSI para colores de consola
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"

// round robin
void ejecutar_round_robin(cola_circular* cc_listos, lista_enlazada* lista_finalizada, pila* historial, int quantum) {
    printf("\n--- iniciando planificacion round robin [quantum: %d] ---\n", quantum);
    
    while (!cc_vacia(cc_listos)) {
        proceso p = desencolar_cc(cc_listos);
        
        printf(GREEN "ejecutando proceso %d" RESET ": tiempo restante %d\n", p.pid, p.tiempo_restante);
       // sleep(1); 
        
        // marcamos el proceso como en ejecucion
        p.estado = EJECUCION;
        apilar(historial, p);
        
        if (p.tiempo_restante > quantum) {
            // el proceso todavia necesita tiempo, lo interrumpimos y regresa a la cola
            p.tiempo_restante -= quantum;
            p.estado = LISTO;
            printf(YELLOW "  quantum expirado" RESET ". proceso %d reencolado con %d restante\n", p.pid, p.tiempo_restante);
            apilar(historial, p);
            encolar_cc(cc_listos, p);
        } else {
            // el proceso termina su trabajo dentro del quantum actual
            printf(RED "  * proceso %d termino su rafaga" RESET ". enviando a lista de finalizados\n", p.pid);
            p.tiempo_restante = 0;
            p.estado = FINALIZADO;
            apilar(historial, p);
            insertar_ordenado_por_pid(lista_finalizada, p);
        }
        //sleep(1); 
    }
    printf("--- fin de round robin ---\n\n");
}
