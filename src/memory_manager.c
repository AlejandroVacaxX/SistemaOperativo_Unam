#include "memory_manager.h"
#include <stdlib.h>
#include <stdio.h>

// creamos el primer bloque que representa toda la memoria disponible al inicio
bloque_memoria* inicializar_memoria(int tamano_total) {
    bloque_memoria* cabeza = (bloque_memoria*)malloc(sizeof(bloque_memoria));
    if (!cabeza) return NULL;
    
    cabeza->inicio = 0;
    cabeza->tamano = tamano_total;
    cabeza->libre = true;
    cabeza->pid = -1;
    cabeza->siguiente = NULL;
    cabeza->anterior = NULL;
    
    return cabeza;
}

// funcion auxiliar para dividir un bloque si es mas grande de lo necesario
void dividir_bloque(bloque_memoria* bloque, int tamano) {
    if (bloque->tamano > tamano) {
        bloque_memoria* nuevo_bloque = (bloque_memoria*)malloc(sizeof(bloque_memoria));
        if (!nuevo_bloque) return;
        
        nuevo_bloque->inicio = bloque->inicio + tamano;
        nuevo_bloque->tamano = bloque->tamano - tamano;
        nuevo_bloque->libre = true;
        nuevo_bloque->pid = -1;
        nuevo_bloque->siguiente = bloque->siguiente;
        nuevo_bloque->anterior = bloque;
        
        if (bloque->siguiente != NULL) {
            bloque->siguiente->anterior = nuevo_bloque;
        }
        
        bloque->siguiente = nuevo_bloque;
        bloque->tamano = tamano;
    }
}

// buscamos el primer bloque libre que tenga espacio suficiente (estrategia rapida)
bloque_memoria* buscar_primer_ajuste(bloque_memoria* cabeza, int tamano) {
    bloque_memoria* actual = cabeza;
    while (actual != NULL) {
        if (actual->libre && actual->tamano >= tamano) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

// buscamos el bloque libre mas pequeño que sea suficiente (estrategia para reducir desperdicio)
bloque_memoria* buscar_mejor_ajuste(bloque_memoria* cabeza, int tamano) {
    bloque_memoria* actual = cabeza;
    bloque_memoria* mejor = NULL;
    while (actual != NULL) {
        if (actual->libre && actual->tamano >= tamano) {
            if (mejor == NULL || actual->tamano < mejor->tamano) {
                mejor = actual;
            }
        }
        actual = actual->siguiente;
    }
    return mejor;
}

// buscamos el bloque libre mas grande disponible (estrategia para dejar huecos grandes)
bloque_memoria* buscar_peor_ajuste(bloque_memoria* cabeza, int tamano) {
    bloque_memoria* actual = cabeza;
    bloque_memoria* peor = NULL;
    while (actual != NULL) {
        if (actual->libre && actual->tamano >= tamano) {
            if (peor == NULL || actual->tamano > peor->tamano) {
                peor = actual;
            }
        }
        actual = actual->siguiente;
    }
    return peor;
}

// funcion principal de asignacion que delega segun la estrategia elegida
bloque_memoria* asignar_memoria(bloque_memoria* cabeza, int pid, int tamano, estrategia_asignacion estrategia) {
    bloque_memoria* objetivo = NULL;
    
    switch (estrategia) {
        case PRIMER_AJUSTE:
            objetivo = buscar_primer_ajuste(cabeza, tamano);
            break;
        case MEJOR_AJUSTE:
            objetivo = buscar_mejor_ajuste(cabeza, tamano);
            break;
        case PEOR_AJUSTE:
            objetivo = buscar_peor_ajuste(cabeza, tamano);
            break;
    }
    
    if (objetivo != NULL) {
        dividir_bloque(objetivo, tamano);
        objetivo->libre = false;
        objetivo->pid = pid;
    }
    
    return objetivo;
}

// simplemente marcamos el bloque como libre para que pueda ser reusado
void liberar_memoria(bloque_memoria* bloque) {
    if (bloque != NULL) {
        bloque->libre = true;
        bloque->pid = -1;
    }
}

// recorremos la lista sumando el tamaño de todos los bloques que estan marcados como libres
int obtener_memoria_libre_total(bloque_memoria* cabeza) {
    int total = 0;
    bloque_memoria* actual = cabeza;
    while (actual != NULL) {
        if (actual->libre) {
            total += actual->tamano;
        }
        actual = actual->siguiente;
    }
    return total;
}

// un hueco es un bloque libre; contamos cuantos de estos hay dispersos por la lista
int contar_huecos_memoria(bloque_memoria* cabeza) {
    int huecos = 0;
    bloque_memoria* actual = cabeza;
    while (actual != NULL) {
        if (actual->libre) {
            huecos++;
        }
        actual = actual->siguiente;
    }
    return huecos;
}

// buscamos entre todos los bloques libres cual es el que tiene la mayor capacidad
int obtener_tamano_hueco_mas_grande(bloque_memoria* cabeza) {
    int tamano_maximo = 0;
    bloque_memoria* actual = cabeza;
    while (actual != NULL) {
        if (actual->libre && actual->tamano > tamano_maximo) {
            tamano_maximo = actual->tamano;
        }
        actual = actual->siguiente;
    }
    return tamano_maximo;
}

// buscamos parejas de bloques libres contiguos para unificarlos en uno solo
void unir_memoria(bloque_memoria* cabeza) {
    bloque_memoria* actual = cabeza;
    while (actual != NULL && actual->siguiente != NULL) {
        if (actual->libre && actual->siguiente->libre) {
            bloque_memoria* siguiente_bloque = actual->siguiente;
            actual->tamano += siguiente_bloque->tamano;
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
void buscar_todos_los_huecos_fuerza_bruta(bloque_memoria* cabeza, int tamano) {
    bloque_memoria* actual = cabeza;
    while (actual != NULL) {
        if (actual->libre && actual->tamano >= tamano) {
            // hueco encontrado
        }
        actual = actual->siguiente;
    }
}

// ayuda a reconstruir los punteros de la lista despues de reorganizar
void reconstruir_direcciones(bloque_memoria* cabeza) {
    int inicio_actual = 0;
    bloque_memoria* actual = cabeza;
    while (actual != NULL) {
        actual->inicio = inicio_actual;
        inicio_actual += actual->tamano;
        actual = actual->siguiente;
    }
}

// compacta la memoria moviendo bloques ocupados al frente de forma recursiva (divide y venceras)
void compactar_memoria_divide_y_venceras(bloque_memoria** cabeza) {
    if (*cabeza == NULL || (*cabeza)->siguiente == NULL) {
        return;
    }
    
    bloque_memoria* lista_ocupados = NULL;
    bloque_memoria* final_ocupados = NULL;
    int total_libre = 0;
    
    bloque_memoria* actual = *cabeza;
    while (actual != NULL) {
        bloque_memoria* siguiente = actual->siguiente;
        if (actual->libre) {
            total_libre += actual->tamano;
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
        bloque_memoria* bloque_libre = (bloque_memoria*)malloc(sizeof(bloque_memoria));
        if (bloque_libre) {
            bloque_libre->tamano = total_libre;
            bloque_libre->libre = true;
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
bloque_memoria* clonar_memoria(bloque_memoria* cabeza) {
    if (cabeza == NULL) return NULL;
    
    bloque_memoria* nueva_cabeza = (bloque_memoria*)malloc(sizeof(bloque_memoria));
    if (!nueva_cabeza) return NULL;
    
    *nueva_cabeza = *cabeza;
    nueva_cabeza->siguiente = clonar_memoria(cabeza->siguiente);
    if (nueva_cabeza->siguiente != NULL) {
        nueva_cabeza->siguiente->anterior = nueva_cabeza;
    }
    
    return nueva_cabeza;
}

// libera todos los nodos de la lista para evitar fugas de memoria durante el backtracking
void liberar_lista_memoria(bloque_memoria* cabeza) {
    bloque_memoria* actual = cabeza;
    while (actual != NULL) {
        bloque_memoria* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
}

// mostramos la ram de forma grafica para que sea facil de entender
void imprimir_mapa_memoria(bloque_memoria* cabeza) {
    bloque_memoria* actual = cabeza;
    printf("mapa de memoria: ");
    while (actual != NULL) {
        if (actual->libre) {
            printf("\033[32m[%d libres]\033[0m", actual->tamano);
        } else {
            printf("\033[31m[p%d:%d]\033[0m", actual->pid, actual->tamano);
        }
        actual = actual->siguiente;
    }
    printf("\n");
}
