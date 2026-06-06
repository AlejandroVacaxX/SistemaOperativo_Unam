#include "fifo.h"
#include <stdio.h>

// el algoritmo fifo procesa los procesos en el orden exacto en que llegaron a la cola
void ejecutar_fifo(cola* cola_listos, lista_enlazada* lista_finalizada, pila* historial) {
    while (!cola_vacia(cola_listos)) {
        Process p = desencolar(cola_listos);
        
        // cambiamos el estado a ejecutandose para iniciar la simulacion
        p.state = RUNNING;
        apilar(historial, p);
        
        // en fifo el proceso corre hasta terminar sin interrupciones
        p.remaining_time = 0;
        p.state = FINISHED;
        
        // registramos el fin del proceso y lo guardamos en la lista de terminados
        apilar(historial, p);
        insertar_ordenado_por_pid(lista_finalizada, p);
    }
}
