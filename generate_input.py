import csv
import random

# script para generar datos aleatorios de procesos para nuestras pruebas del simulador
def generar_procesos_aleatorios(nombre_archivo, cantidad):
    # abrimos el archivo csv para escritura asegurando que los saltos de linea sean correctos
    with open(nombre_archivo, mode='w', newline='') as archivo:
        escritor = csv.writer(archivo)
        
        # escribimos los encabezados de las columnas para identificar cada dato
        escritor.writerow(['pid', 'burst_time', 'priority', 'memory_required'])
        
        # generamos cada proceso con valores dentro de rangos razonables para la simulacion
        for i in range(1, cantidad + 1):
            pid = i
            burst_time = random.randint(1, 20)
            priority = random.randint(1, 5)
            memory_required = random.randint(10, 100)
            
            escritor.writerow([pid, burst_time, priority, memory_required])

# ejecutamos la generacion de una tanda inicial de 10 procesos de prueba
if __name__ == "__main__":
    generar_procesos_aleatorios('input.csv', 10)
