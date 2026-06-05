#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "memory_block.h"

typedef enum {
    PRIMER_AJUSTE,
    MEJOR_AJUSTE,
    PEOR_AJUSTE
} estrategia_asignacion;

// inicializa la memoria principal con un unico bloque vacio del tamaño total
bloque_memoria* inicializar_memoria(int tamano_total);

// intenta asignar un bloque de memoria para un proceso especifico usando una estrategia
bloque_memoria* asignar_memoria(bloque_memoria* cabeza, int pid, int tamano, estrategia_asignacion estrategia);

// libera un bloque de memoria asociado a un proceso
void liberar_memoria(bloque_memoria* bloque);

// calcula la cantidad total de memoria libre en el sistema
int obtener_memoria_libre_total(bloque_memoria* cabeza);

// cuenta cuantos huecos (bloques libres separados) existen actualmente
int contar_huecos_memoria(bloque_memoria* cabeza);

// determina el tamaño del hueco mas grande disponible
int obtener_tamano_hueco_mas_grande(bloque_memoria* cabeza);

// recorre la lista de memoria uniendo bloques libres que esten uno junto al otro
void unir_memoria(bloque_memoria* cabeza);

// busca exhaustivamente todos los huecos que pueden contener un tamaño especifico
// imprime la ubicacion y tamaño de cada hueco encontrado
void buscar_todos_los_huecos_fuerza_bruta(bloque_memoria* cabeza, int tamano);

// reorganiza la memoria para mover todos los bloques libres al final
// utiliza una estrategia de divide y venceras para procesar la lista
void compactar_memoria_divide_y_venceras(bloque_memoria** cabeza);

// crea una copia exacta de la lista de memoria actual para recuperacion posterior
bloque_memoria* clonar_memoria(bloque_memoria* cabeza);

// libera toda la memoria ocupada por la lista de bloques
void liberar_lista_memoria(bloque_memoria* cabeza);

// imprime una representacion visual de la memoria en formato [P1:100][libre:50]
void imprimir_mapa_memoria(bloque_memoria* cabeza);

#endif // MEMORY_MANAGER_H
