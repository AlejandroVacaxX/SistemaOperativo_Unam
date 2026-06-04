#include "cola_circular.h"

// inicializa la cola circular poniendola vacia
void iniciar_cc(cola_circular* cc) {
    cc->frente = 0;
    cc->anterior = -1;
    cc->contador = 0;
}

// verifica si la cola circular esta vacia
bool cc_vacia(cola_circular* cc) {
    return cc->contador == 0;
}

// verifica si la cola circular alcanzo su limite de capacidad
bool cc_llena(cola_circular* cc) {
    return cc->contador == MAX_CC_TAMANO;
}

// encola un proceso en la cola circular
bool encolar_cc(cola_circular* cc, process p) {
    if (cc_llena(cc)) {
        return false;
    }
    
    cc->anterior = (cc->anterior + 1) % MAX_CC_TAMANO;
    cc->items[cc->anterior] = p;
    cc->contador++;
    
    return true;
}

// desencola y retorna el proceso al frente de la cola circular
process desencolar_cc(cola_circular* cc) {
    process p = {0}; // proceso vacio por defecto
    if (!cc_vacia(cc)) {
        p = cc->items[cc->frente];
        cc->frente = (cc->frente + 1) % MAX_CC_TAMANO;
        cc->contador--;
    }
    return p;
}
