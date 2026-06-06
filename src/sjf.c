#include "sjf.h"
#include <stdbool.h>

// el algoritmo sjf aplica una estrategia codiciosa para elegir el proceso con menor tiempo de rafaga
void ejecutar_sjf(Process procesos[], int n, lista_enlazada* lista_finalizada, pila* historial) {
    bool completado[n];
    for (int i = 0; i < n; i++) {
        completado[i] = false;
    }
    
    int contador_completados = 0;
    while (contador_completados < n) {
        int indice_mas_corto = -1;
        int rafaga_minima = 2147483647; // maximo valor entero para comparar
        
        // buscamos el proceso que no ha terminado con la rafaga mas pequeña
        for (int i = 0; i < n; i++) {
            if (!completado[i] && procesos[i].burst_time < rafaga_minima) {
                rafaga_minima = procesos[i].burst_time;
                indice_mas_corto = i;
            }
        }
        
        if (indice_mas_corto != -1) {
            Process* p = &procesos[indice_mas_corto];
            
            // simulamos el cambio de estado a ejecucion
            p->state = RUNNING;
            apilar(historial, *p);
            
            // en sjf no apropiativo el proceso corre hasta terminar
            p->remaining_time = 0;
            p->state = FINISHED;
            
            // registramos el final y lo pasamos a la lista de procesos terminados
            apilar(historial, *p);
            insertar_ordenado_por_pid(lista_finalizada, *p);
            
            completado[indice_mas_corto] = true;
            contador_completados++;
        }
    }
}
