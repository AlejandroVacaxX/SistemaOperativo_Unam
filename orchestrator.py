import subprocess
import time
import os
import generate_input
import visualize_results

# orquestador con interfaz de consola profesional para mejorar la experiencia de usuario
def main():
    print("🚀 Iniciando Simulador de Sistema Operativo...")
    
    # fase 1: generacion de datos
    print("⚙️ Fase 1: Generando lote de procesos aleatorios...", end=" ", flush=True)
    generate_input.generar_procesos_aleatorios('input.csv', 100)
    print("[OK]")

    # fase 2: compilacion
    print("⚙️ Fase 2: Compilando motor de simulacion en C...", end=" ", flush=True)
    fuentes = [
        "src/main.c", "src/fifo.c", "src/round_robin.c", "src/sjf.c",
        "src/queue.c", "src/circular_queue.c", "src/linked_list.c", 
        "src/stack.c", "src/csv_parser.c", "src/csv_exporter.c"
    ]
    comando_compilacion = ["gcc"] + fuentes + ["-o", "simulador"]
    try:
        subprocess.run(comando_compilacion, check=True)
        print("[OK]")
    except subprocess.CalledProcessError:
        print("[ERROR]")
        return

    # fase 3: ejecucion de algoritmos
    print("⚙️ Fase 3: Ejecutando algoritmos de planificacion...")
    algoritmos = [
        ("fifo", "FIFO Scheduler"),
        ("rr", "Round Robin (Q=2)"),
        ("sjf", "Shortest Job First (SJF)")
    ]

    for cod, nombre in algoritmos:
        print(f"   Corriendo {nombre}...", end=" ", flush=True)
        inicio = time.time()
        subprocess.run(["./simulador", cod, "input.csv"], check=True)
        fin = time.time()
        print(f"[Terminado en {fin - inicio:.3f}s]")

    # fase 4: analisis y graficacion
    print("📊 Fase 4: Analizando resultados y generando graficas...", end=" ", flush=True)
    visualize_results.analizar_resultados('output.csv')
    print("[OK]")

    print("\n✅ Simulacion completada con exito.")
    print("📁 Las graficas de benchmarking han sido guardadas en la carpeta actual.")

if __name__ == "__main__":
    main()
