# bitacora de desarrollo con inteligencia artificial

## resumen del proceso
el desarrollo del simulador de sistema operativo se realizo de forma iterativa y modular dividiendo el trabajo en fases logicas. empezamos estableciendo las estructuras de datos basicas en lenguaje c como procesos y bloques de memoria. posteriormente se implementaron los algoritmos de planificacion de cpu y finalmente el administrador de memoria ram con sus funciones de compactacion y coalecencia. la ultima etapa consistio en integrar todo con python para la automatizacion y visualizacion de datos.

## correcciones y ajustes solicitados por el usuario
durante la ejecucion recibimos retroalimentacion valiosa que ayudo a mejorar la calidad del producto final. una de las correcciones principales fue la legibilidad de las graficas de rendimiento ya que inicialmente se generaban demasiados procesos y las etiquetas se encimaban. se ajusto el limite a veinticinco procesos para mantener la claridad visual. tambien se modifico el exportador de c para que los estados de los procesos fueran palabras legibles en lugar de codigos numericos en el archivo csv. por ultimo se añadio un sistema de pausas y una representacion grafica de bloques en la consola para que la demostracion fuera mas facil de seguir para un humano.

## analisis de complejidad de los algoritmos
los planificadores fifo y round robin operan con una complejidad de tiempo lineal respecto al numero de procesos ya que recorren las colas de forma secuencial. el planificador sjf requiere buscar el proceso mas corto en cada paso lo que eleva su complejidad ligeramente pero sigue siendo eficiente para el volumen de datos manejado. en cuanto a la memoria los algoritmos de primer y mejor ajuste recorren la lista de bloques en busca de espacio libre. la coalecencia y la compactacion tambien recorren la lista de bloques de memoria una o dos veces para reorganizar los nodos y eliminar la fragmentacion. el uso de memoria es proporcional a la cantidad de procesos activos y bloques generados en la ram.

## reflexion final
el uso de inteligencia artificial permitio acelerar la escritura de codigo siguiendo reglas estrictas de formato y estilo. se respeto siempre el flujo de trabajo de git con ramas independientes para cada mejora y commits atomicos descriptivos. la integracion final logra un equilibrio entre un motor de calculo eficiente en c y una interfaz de usuario descriptiva y visual en python.
