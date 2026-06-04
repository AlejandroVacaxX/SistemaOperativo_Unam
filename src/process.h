#ifndef PROCESS_H
#define PROCESS_H

// definicion de los estados posibles por los que pasa un proceso en nuestro simulador
typedef enum {
    READY,
    RUNNING,
    BLOCKED,
    FINISHED
} process_state;

// estructura principal que contiene la informacion de un proceso a ser planificado
typedef struct {
    int pid;
    int burst_time;
    int remaining_time;
    int priority;
    int memory_required;
    process_state state;
} process;

#endif // PROCESS_H
