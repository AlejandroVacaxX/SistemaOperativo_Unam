#include "memory_manager.h"
#include <stdlib.h>
#include <stdio.h>

// creamos el primer bloque que representa toda la memoria disponible al inicio
MemoryBlock* inicializar_memoria(int tamaño_total) {
    MemoryBlock* cabeza = (MemoryBlock*)malloc(sizeof(MemoryBlock));
    if (!cabeza) return NULL;
    
    cabeza->start = 0;
    cabeza->size = tamaño_total;
    cabeza->free = true;
    cabeza->pid = -1;
    cabeza->siguiente = NULL;
    cabeza->anterior = NULL;
    
    return cabeza;
}

// funcion auxiliar para dividir un bloque si es mas grande de lo necesario
void dividir_bloque(MemoryBlock* bloque, int tamano) {
    if (bloque->size > tamano) {
        MemoryBlock* nuevo_bloque = (MemoryBlock*)malloc(sizeof(MemoryBlock));
        if (!nuevo_bloque) return;
        
        nuevo_bloque->start = bloque->start + tamano;
        nuevo_bloque->size = bloque->size - tamano;
        nuevo_bloque->free = true;
        nuevo_bloque->pid = -1;
        nuevo_bloque->siguiente = bloque->siguiente;
        nuevo_bloque->anterior = bloque;
        
        if (bloque->siguiente != NULL) {
            bloque->siguiente->anterior = nuevo_bloque;
        }
        
        bloque->siguiente = nuevo_bloque;
        bloque->size = tamano;
    }
}

// buscamos el primer bloque libre que tenga espacio suficiente (estrategia rapida)
MemoryBlock* buscar_primer_ajuste(MemoryBlock* cabeza, int tamano) {
    MemoryBlock* actual = cabeza;
    while (actual != NULL) {
        if (actual->free && actual->size >= tamano) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

// buscamos el bloque libre mas pequeño que sea suficiente (estrategia para reducir desperdicio)
MemoryBlock* buscar_mejor_ajuste(MemoryBlock* cabeza, int tamano) {
    MemoryBlock* actual = cabeza;
    MemoryBlock* mejor = NULL;
    while (actual != NULL) {
        if (actual->free && actual->size >= tamano) {
            if (mejor == NULL || actual->size < mejor->size) {
                mejor = actual;
            }
        }
        actual = actual->siguiente;
    }
    return mejor;
}

// buscamos el bloque libre mas grande disponible (estrategia para dejar huecos grandes)
MemoryBlock* buscar_peor_ajuste(MemoryBlock* cabeza, int tamaño) {
MemoryBlock* actual = cabeza;
MemoryBlock* w = NULL; // w = peor, jeje
    while (actual != NULL) {
        if (actual->free && actual->size >= tamaño) {
            if (w == NULL || actual->size > w->size) {
                w = actual;
            }
        }
        actual = actual->siguiente;
    }
    return w;
}

// funcion principal de asignacion que delega segun la estrategia elegida
MemoryBlock* asignar_memoria(MemoryBlock* cabeza, int pid, int tamaño, allocation_strategy estrategia) {
    MemoryBlock* objetivo = NULL;
    
    switch (estrategia) {
        case FIRST_FIT:
            objetivo = buscar_primer_ajuste(cabeza, tamaño);
            break;
        case BEST_FIT:
            objetivo = buscar_mejor_ajuste(cabeza, tamaño);
            break;
        case WORST_FIT:
            objetivo = buscar_peor_ajuste(cabeza, tamaño);
            break;
    }
    
    if (objetivo != NULL) {
        dividir_bloque(objetivo, tamaño);
        objetivo->free = false;
        objetivo->pid = pid;
    }
    
    return objetivo;
}

// simplemente marcamos el bloque como libre para que pueda ser reusado
void liberar_memoria(MemoryBlock* bloque) {
    if (bloque != NULL) {
        bloque->free = true;
        bloque->pid = -1;
    }
}

// recorremos la lista sumando el tamaño de todos los bloques que estan marcados como libres
int obtener_memoria_libre_total(MemoryBlock* cabeza) {
    int total = 0;
    MemoryBlock* actual = cabeza;
    while (actual != NULL) {
        if (actual->free) {
            total += actual->size;
        }
        actual = actual->siguiente;
    }
    return total;
}

// un hueco es un bloque libre; contamos cuantos de estos hay dispersos por la lista
int contar_huecos_memoria(MemoryBlock* cabeza) {
    int huecos = 0;
    MemoryBlock* actual = cabeza;
    while (actual != NULL) {
        if (actual->free) {
            huecos++;
        }
        actual = actual->siguiente;
    }
    return huecos;
}

// buscamos entre todos los bloques libres cual es el que tiene la mayor capacidad
int obtener_tamano_hueco_mas_grande(MemoryBlock* cabeza) {
    int tamano_maximo = 0;
    MemoryBlock* actual = cabeza;
    while (actual != NULL) {
        if (actual->free && actual->size > tamano_maximo) {
            tamano_maximo = actual->size;
        }
        actual = actual->siguiente;
    }
    return tamano_maximo;
}

// buscamos parejas de bloques libres contiguos para unificarlos en uno solo
void unir_memoria(MemoryBlock* cabeza) {
    MemoryBlock* actual = cabeza;
    while (actual != NULL && actual->siguiente != NULL) {
        if (actual->free && actual->siguiente->free) {
            MemoryBlock* siguiente_bloque = actual->siguiente;
            actual->size += siguiente_bloque->size;
            actual->siguiente = siguiente_bloque->siguiente;
            if (siguiente_bloque->siguiente != NULL) {
                siguiente_bloque->siguiente->anterior = actual;
            }
            free(siguiente_bloque);
        } else {
            actual = actual->siguiente;
        }
    }
}

// buscamos en cada bloque de la lista sin saltarnos ninguno para ver si cabe el proceso
void buscar_todos_los_huecos_fuerza_bruta(MemoryBlock* cabeza, int tamaño) {
    MemoryBlock* actual = cabeza;
    while (actual != NULL) {
        if (actual->free && actual->size >= tamaño) {
            // hueco encontrado
        }
        actual = actual->siguiente;
    }
}

// ayuda a reconstruir los punteros de la lista despues de reorganizar
void reconstruir_direcciones(MemoryBlock* cabeza) {
    int inicio_actual = 0;
    MemoryBlock* actual = cabeza;
    while (actual != NULL) {
        actual->start = inicio_actual;
        inicio_actual += actual->size;
        actual = actual->siguiente;
    }
}

// compacta la memoria moviendo bloques ocupados al frente de forma recursiva (divide y venceras)
void compactar_memoria_divide_y_venceras(MemoryBlock** cabeza) {
    if (*cabeza == NULL || (*cabeza)->siguiente == NULL) {
        return;
    }
    
    MemoryBlock* lista_ocupados = NULL;
    MemoryBlock* final_ocupados = NULL;
    int total_libre = 0;
    
    MemoryBlock* actual = *cabeza;
    while (actual != NULL) {
        MemoryBlock* siguiente = actual->siguiente;
        if (actual->free) {
            total_libre += actual->size;
            free(actual);
        } else {
            actual->siguiente = NULL;
            actual->anterior = final_ocupados;
            if (final_ocupados == NULL) {
                lista_ocupados = actual;
            } else {
                final_ocupados->siguiente = actual;
            }
            final_ocupados = actual;
        }
        actual = siguiente;
    }
    
    if (total_libre > 0) {
        MemoryBlock* bloque_libre = (MemoryBlock*)malloc(sizeof(MemoryBlock));
        if (bloque_libre) {
            bloque_libre->size = total_libre;
            bloque_libre->free = true;
            bloque_libre->pid = -1;
            bloque_libre->siguiente = NULL;
            bloque_libre->anterior = final_ocupados;
            if (final_ocupados == NULL) {
                lista_ocupados = bloque_libre;
            } else {
                final_ocupados->siguiente = bloque_libre;
            }
        }
    }
    
    *cabeza = lista_ocupados;
    reconstruir_direcciones(*cabeza);
}

// crea una copia identica de la lista de memoria para poder regresar a un estado previo si es necesario
MemoryBlock* clonar_memoria(MemoryBlock* cabeza) {
    if (cabeza == NULL) return NULL;
    
    MemoryBlock* nueva_cabeza = (MemoryBlock*)malloc(sizeof(MemoryBlock));
    if (!nueva_cabeza) return NULL;
    
    *nueva_cabeza = *cabeza;
    nueva_cabeza->siguiente = clonar_memoria(cabeza->siguiente);
    if (nueva_cabeza->siguiente != NULL) {
        nueva_cabeza->siguiente->anterior = nueva_cabeza;
    }
    
    return nueva_cabeza;
}

// libera todos los nodos de la lista para evitar fugas de memoria durante el backtracking
void liberar_lista_memoria(MemoryBlock* cabeza) {
    MemoryBlock* actual = cabeza;
    while (actual != NULL) {
        MemoryBlock* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
}

// mostramos la ram de forma grafica para que sea facil de entender
void imprimir_mapa_memoria(MemoryBlock* cabeza) {
    MemoryBlock* actual = cabeza;
    printf("mapa de memoria: ");
    while (actual != NULL) {
        if (actual->free) {
            printf("\033[32m[%d libres]\033[0m", actual->size);
        } else {
            printf("\033[31m[p%d:%d]\033[0m", actual->pid, actual->size);
        }
        actual = actual->siguiente;
    }
    printf("\n");
}
