# guia de conocimiento del sistema operativo

## archivos de lenguaje c (backend)
el motor del simulador esta escrito en c para garantizar eficiencia y control total sobre las estructuras de datos.

### src/main.c
es el punto de entrada principal. recibe argumentos desde python para decidir que algoritmo de planificacion ejecutar o si debe mostrar la demostracion visual de la memoria ram.

### src/process.h
contiene las definiciones basicas de los procesos. aqui se encuentra la estructura que guarda el pid, el tiempo de rafaga, la prioridad y la memoria requerida, ademas del enum para los estados (listo, ejecutando, bloqueado, terminado).

### src/memory_block.h
define la estructura de un bloque de memoria para la lista doblemente enlazada. incluye punteros al bloque anterior y siguiente, el tamaño del bloque y si esta libre u ocupado por un proceso.

### src/memory_manager.c y .h
implementan toda la logica de gestion de memoria ram. incluye las estrategias de asignacion como first fit, best fit y worst fit, ademas de los algoritmos de coalescencia para unir bloques libres y compactacion por divide y venceras.

### src/fifo.c y .h
implementan el planificador first in first out. procesa los procesos en el orden estricto de llegada usando una cola dinamica.

### src/round_robin.c y .h
implementan el planificador circular con quantum. usa una cola circular y permite la interrupcion de procesos si su tiempo de rafaga supera el quantum establecido. incluye colores y pausas para la demostracion.

### src/sjf.c y .h
implementan el planificador shortest job first. utiliza una estrategia codiciosa para seleccionar siempre el proceso con el menor tiempo de rafaga restante de entre todos los disponibles.

### src/stack.c y .h
estructura de pila utilizada para mantener un historial de los cambios de estado de los procesos y permitir operaciones de backtracking en la memoria.

### src/queue.c y .h
estructura de cola dinamica simple utilizada principalmente por el planificador fifo.

### src/circular_queue.c y .h
estructura de cola circular de tamaño fijo diseñada especificamente para el funcionamiento del algoritmo round robin.

### src/linked_list.c y .h
implementacion de una lista enlazada ordenada por pid que se utiliza para almacenar y organizar los procesos que han finalizado su ejecucion.

### src/csv_parser.c y .h
funciones encargadas de leer el archivo generado por python y convertir cada linea en una estructura de proceso dentro de la memoria de c.

### src/csv_exporter.c y .h
funciones encargadas de tomar la lista de procesos terminados y escribir sus resultados finales en un archivo csv para que python pueda procesarlos.

## archivos de lenguaje python (frontend)
python se encarga de la orquestacion, la generacion de datos y la visualizacion grafica.

### orchestrator.py
es el script principal que el usuario debe ejecutar. coordina la generacion de procesos, la compilacion del codigo c mediante gcc y la ejecucion de las demostraciones visuales con pausas controladas.

### generate_input.py
script especializado en crear el archivo de entrada con datos aleatorios de procesos asegurando que la simulacion tenga siempre datos frescos y variados para probar.

### visualize_results.py
usa las librerias pandas y seaborn para leer los resultados finales y generar graficas de barras que permiten analizar visualmente el rendimiento de los algoritmos.

## archivos de documentacion
* bitacora_ia.md: registro de todo el proceso de desarrollo con la inteligencia artificial y analisis de complejidad.
* analisis_algoritmos.md: resumen de alto nivel sobre las decisiones de diseño y el funcionamiento de los algoritmos.
* conocimiento.md: este archivo explicativo sobre la estructura del proyecto.
