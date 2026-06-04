import subprocess
import time
import os
import generate_input
import visualize_results
from sistemaOperativoComandosFaltos import boot_os


def main():
    boot_os()

    
    # generacion de pocos procesos para legibilidad
    print("generando lote de procesos para la demostracion ", end=" ", flush=True)
    generate_input.generar_procesos_aleatorios('input.csv', 50) # con esto podemos variar la cantidad de procesos
   # time.sleep(1) # para benchmark comentamos los sleep, tambien en los codigos C
    print("OK")

    # compilacion, gracias a estas lineas de comando python manda a ejecutar todos nuestros codigos de C
    print("compilando motor de simulacion en C ", end=" ", flush=True)
    fuentes = [
        "src/main.c", "src/fifo.c", "src/round_robin.c", "src/sjf.c",
        "src/cola.c", "src/cola_circular.c", "src/linked_list.c", 
        "src/stack.c", "src/csv_parser.c", "src/csv_exporter.c", "src/memory_manager.c"
    ]
    comando_compilacion = ["gcc"] + fuentes + ["-o", "simulador"]
    try:
        subprocess.run(comando_compilacion, check=True)
        #time.sleep(1)
        print("ok")
    except subprocess.CalledProcessError:
        print("error")
        return

    # demostracion de memoria
    print("\n demostracion de gestion de memoria")
    #time.sleep(1)
    subprocess.run(["./simulador", "demo_memoria"], check=True)
    #time.sleep(2)

    # ejecucion de planificadores con medicion de rendimiento
    print("\n-------------------------------------------------")
    print("ejecutando planificadores y midiendo rendimiento...")
    
    algoritmos = [
        ("fifo", "fifo scheduler"),
        ("rr", "round robin (q=2)"),
        ("sjf", "shortest job first (sjf)")
    ]
    
    resultados_bench = []
    
    for cod, nombre in algoritmos:
        print(f"   corriendo {nombre}...", end=" ", flush=True)
        inicio = time.perf_counter() # alta precision
        subprocess.run(["./simulador", cod, "input.csv"], check=True)
        fin = time.perf_counter()
        duracion = fin - inicio
        print(f"[terminado en {duracion:.6f}s]")
        resultados_bench.append([nombre, duracion])

    # guardamos los tiempos en un csv para analisis posterior
    import csv
    with open('benchmarks.csv', mode='w', newline='') as f:
        escritor = csv.writer(f)
        escritor.writerow(['algoritmo', 'tiempo_segundos'])
        escritor.writerows(resultados_bench)
    print("📁 datos guardados en 'benchmarks.csv'")

    # analisis y graficacion
    print("generando graficas de los procesos", end=" ", flush=True)
    visualize_results.analizar_resultados('output.csv')
   # time.sleep(1)
    print("ok")

    print("\ndemostracion completada con exito")
    print(" archivo 'grafica_rendimiento.png' generado.")

if __name__ == "__main__":
    main()
