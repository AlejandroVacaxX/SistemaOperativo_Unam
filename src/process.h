#ifndef PROCESS_H
#define PROCESS_H

// creacion de structuras siguiendo el ejemplo del pdf
typedef enum {
    LISTO,
    EJECUCION,
    BLOQUEADO,
    FINALIZADO
} estado_proceso;

// estructura principal que contiene la informacion de un proceso a ser planificado
typedef struct {
    int pid;
    int tiempo_rafaga;
    int tiempo_restante;
    int prioridad;
    int memoria_requerida;
    estado_proceso estado;
} proceso;

#endif // PROCESS_H
