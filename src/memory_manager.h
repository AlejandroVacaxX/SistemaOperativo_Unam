#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "memory_block.h"

typedef enum {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
} allocation_strategy;


// inicializa la memoria principal con un unico bloque vacio del tamaño total
MemoryBlock* inicializar_memoria(int tamano_total);

// intenta asignar un bloque de memoria para un proceso especifico usando una estrategia
MemoryBlock* asignar_memoria(MemoryBlock* cabeza, int pid, int tamano, allocation_strategy estrategia);

// libera un bloque de memoria asociado a un proceso
void liberar_memoria(MemoryBlock* bloque);

// calcula la cantidad total de memoria libre en el sistema
int obtener_memoria_libre_total(MemoryBlock* cabeza);

// cuenta cuantos huecosexisten actualmente
int contar_huecos_memoria(MemoryBlock* cabeza);

// determina el tamaño del hueco mas grande disponible
int obtener_tamano_hueco_mas_grande(MemoryBlock* cabeza);

// recorre la lista de memoria uniendo bloques libres que esten uno junto al otro
void unir_memoria(MemoryBlock* cabeza);

// busca exhaustivamente todos los huecos que pueden contener un tamaño especifico
// imprime la ubicacion y tamaño de cada hueco encontrado
void buscar_todos_los_huecos_fuerza_bruta(MemoryBlock* cabeza, int tamano);

// reorganiza la memoria para mover todos los bloques libres al final
// utiliza una estrategia de divide y venceras para procesar la lista
void compactar_memoria_divide_y_venceras(MemoryBlock** cabeza);

// crea una copia exacta de la lista de memoria actual para recuperacion posterior
MemoryBlock* clonar_memoria(MemoryBlock* cabeza);

// libera toda la memoria 
void liberar_lista_memoria(MemoryBlock* cabeza);


void imprimir_mapa_memoria(MemoryBlock* cabeza);

#endif // MEMORY_MANAGER_H
