import subprocess
import time
import os
import generate_input
import visualize_results

# orquestador con pausas (sleep) para facilitar la lectura de la simulacion
def main():
    print("🚀 iniciando demostracion detallada del sistema operativo...")
    time.sleep(1)
    
    # fase 1: generacion de pocos procesos para legibilidad
    print("⚙️ fase 1: generando lote de 5 procesos para la demostracion...", end=" ", flush=True)
    generate_input.generar_procesos_aleatorios('input.csv', 5)
    time.sleep(1)
    print("[ok]")

    # fase 2: compilacion
    print("⚙️ fase 2: compilando motor de simulacion en c...", end=" ", flush=True)
    fuentes = [
        "src/main.c", "src/fifo.c", "src/round_robin.c", "src/sjf.c",
        "src/cola.c", "src/cola_circular.c", "src/linked_list.c", 
        "src/stack.c", "src/csv_parser.c", "src/csv_exporter.c", "src/memory_manager.c"
    ]
    comando_compilacion = ["gcc"] + fuentes + ["-o", "simulador"]
    try:
        subprocess.run(comando_compilacion, check=True)
        time.sleep(1)
        print("[ok]")
    except subprocess.CalledProcessError:
        print("[error]")
        return

    # fase 3: demostracion de memoria
    print("\n⚙️ fase 3: demostracion de gestion de memoria (visualizacion de bloques)")
    time.sleep(1)
    subprocess.run(["./simulador", "demo_memoria"], check=True)
    time.sleep(2)

    # fase 4: ejecucion detallada de round robin
    print("⚙️ fase 4: ejecutando round robin con visualizacion de quantum...")
    time.sleep(1)
    subprocess.run(["./simulador", "rr", "input.csv"], check=True)
    time.sleep(2)

    # fase 5: analisis y graficacion
    print("📊 fase 5: generando graficas de los 5 procesos...", end=" ", flush=True)
    visualize_results.analizar_resultados('output.csv')
    time.sleep(1)
    print("[ok]")

    print("\n✅ demostracion completada con exito.")
    print("📁 puedes revisar 'grafica_rendimiento.png' para ver los resultados visuales.")

if __name__ == "__main__":
    main()
