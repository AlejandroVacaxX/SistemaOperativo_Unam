# resumen de algoritmos y decisiones de diseño

## planificadores de procesos
para la gestion de la cpu elegimos tres enfoques que cubren las necesidades basicas de un sistema operativo. el primero fue fifo porque es la forma mas natural de procesar tareas en el orden en que llegan, usando una cola simple para mantener la justicia basica. luego incluimos round robin para dar interactividad al sistema; aqui usamos una cola circular y un quantum para asegurar que ningun proceso se adueñe de la cpu por demasiado tiempo. finalmente usamos sjf con un enfoque codicioso para optimizar el tiempo de espera promedio, eligiendo siempre la tarea mas corta disponible.

## administrador de memoria
la memoria se manejo como una lista doblemente enlazada de bloques para poder navegar en ambos sentidos facilmente, lo que es vital para unir espacios vacios. implementamos estrategias greedy como first fit por su rapidez, best fit para cuidar el espacio y worst fit para intentar dejar huecos grandes aprovechables. incluimos un algoritmo de coalescencia que revisa bloques vecinos para combatir la fragmentacion de forma automatica.

## algoritmos avanzados
usamos busqueda exhaustiva por fuerza bruta para encontrar todos los huecos posibles cuando se requiere un analisis detallado del estado de la memoria. para la compactacion aplicamos una idea de divide y venceras que separa lo ocupado de lo libre y reconstruye la lista para dejar un solo bloque grande al final. tambien añadimos backtracking para poder guardar estados previos de la memoria y recuperarlos si una operacion de asignacion no resulta favorable.

## integracion y analisis
la conexion entre c y python mediante archivos csv permitio separar la logica pesada de la simulacion del analisis de datos. python se encarga de la generacion de pruebas y de la parte visual con graficas de rendimiento, mientras que c resuelve toda la algoritmia de bajo nivel de forma eficiente.
