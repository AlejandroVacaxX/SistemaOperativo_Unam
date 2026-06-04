import subprocess
import os

# script para automatizar la compilacion y ejecucion del simulador
def ejecutar_simulacion():
    # definimos los archivos fuente necesarios para la compilacion
    fuentes = [
        "src/main.c", "src/fifo.c", "src/queue.c", "src/linked_list.c", 
        "src/stack.c", "src/csv_parser.c", "src/csv_exporter.c"
    ]
    
    # comando para compilar usando gcc
    comando_compilacion = ["gcc"] + fuentes + ["-o", "simulador"]
    
    # intentamos compilar el codigo fuente de c
    try:
        subprocess.run(comando_compilacion, check=True)
        # si la compilacion es exitosa, ejecutamos el binario resultante
        subprocess.run(["./simulador"], check=True)
    except subprocess.CalledProcessError as e:
        # manejamos errores en caso de fallo en la compilacion o ejecucion
        pass

if __name__ == "__main__":
    # ejecutamos la generacion de datos antes de la simulacion
    import generate_input
    generate_input.generar_procesos_aleatorios('input.csv', 10)
    
    ejecutar_simulacion()
