#include "cola_circular.h"

// inicializa la cola circular poniendola vacia
void iniciar_cc(cola_circular* cc) {
    cc->frente = 0;
    cc->final = -1;
    cc->contador = 0;
}

// verifica si la cola circular esta vacia
bool cc_vacia(cola_circular* cc) {
    return cc->contador == 0;
}

// verifica si la cola circular alcanzo su limite de capacidad
bool cc_llena(cola_circular* cc) {
    return cc->contador == MAX_CC_TAMAÑO;
}

// encola un proceso en la cola circular
bool encolar_cc(cola_circular* cc, Process p) {
    if (cc_llena(cc)) {
        return false;
    }
    
    cc->final = (cc->final + 1) % MAX_CC_TAMAÑO;
    cc->elementos[cc->final] = p;
    cc->contador++;
    return true;
}

// desencola y retorna el proceso al frente de la cola circular
Process desencolar_cc(cola_circular* cc) {
    Process p_vacio = {0};
    if (cc_vacia(cc)) {
        return p_vacio;
    }
    
    Process p = cc->elementos[cc->frente];
    cc->frente = (cc->frente + 1) % MAX_CC_TAMAÑO;
    cc->contador--;
    return p;
}
