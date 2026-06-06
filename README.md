# Simulador de Sistema Operativo

## Descripción del Sistema

Este proyecto es un **Simulador de Sistema Operativo** construido bajo una estricta arquitectura híbrida que integra dos lenguajes de programación para aprovechar al máximo sus fortalezas:

* **Núcleo y Lógica (C):** Toda la lógica pesada, simulaciones, estructuras de datos (colas, listas doblemente enlazadas, pilas), algoritmos de planificación (FIFO, Round Robin, SJF) y la gestión de la memoria dinámica (asignación, liberación y coalescencia de bloques) se ejecutan de manera nativa en **C**. Esto garantiza un alto rendimiento, manejo real a bajo nivel y velocidad.
* **Orquestación y Análisis (Python):** Se encarga de la generación de datos de prueba (procesos aleatorios), la ejecución del binario en C a través de subprocesos, la recolección de los resultados, y la visualización de datos. Python genera métricas de rendimiento y gráficas utilizando librerías como `pandas`, `matplotlib` y `seaborn`.

**Puente de Comunicación:** La integración entre ambos entornos se realiza mediante archivos `.csv` (`input.csv`, `output.csv`), permitiendo un intercambio de información asíncrono, persistente y ordenado.

## Por qué de la Salida de Consola

La salida por consola está intencionalmente diseñada para ser exhaustiva (**verbose**). Su objetivo principal no es solo mostrar un resultado final, sino **trazar de forma transparente el comportamiento interno del sistema operativo en cada instante de tiempo**. 

Al observar la consola, podrás auditar visualmente:
- Los cambios de contexto de los procesos (transiciones entre estados: `READY`, `RUNNING`, `BLOCKED`, `FINISHED`).
- La toma de decisiones de los planificadores de CPU (por ejemplo, interrupciones por *Quantum* en Round Robin o selecciones por tiempo más corto en SJF).
- El estado de la memoria paso a paso (qué algoritmos de asignación como *First Fit* o *Best Fit* se usan, dónde ocurre la fragmentación y cómo se fusionan los bloques liberados).
- La validación del análisis de complejidad (Big O) en tiempo real mediante las operaciones en colas y listas.

---

## Instrucciones de Ejecución para Windows

A continuación, se detallan los pasos necesarios para configurar y ejecutar el entorno del simulador en un sistema operativo Windows, asegurando que tanto Python como las librerías necesarias queden aisladas en su propio entorno virtual.

### Prerrequisitos
1. **Python 3.x:** Instalado y agregado al `PATH` del sistema.
2. **Compilador de C:** Necesitas herramientas como MinGW (GCC) instaladas en tu sistema para poder compilar el núcleo en C.

### Paso 1: Compilar la lógica de C
Abre una terminal (PowerShell o CMD) en la raíz del proyecto y compila el código fuente en la carpeta `src`:
```bash
gcc src/*.c -o simulador.exe
```

### Paso 2: Crear el Entorno Virtual (venv)
Es necesario crear un entorno aislado para mantener organizadas las dependencias de Python del proyecto. En la misma terminal ejecuta:
```bash
python -m venv venv
```

### Paso 3: Activar el Entorno Virtual
Para comenzar a utilizar el entorno recién creado, actívalo con el siguiente comando:
```bash
# Si usas CMD (Símbolo del sistema):
venv\Scripts\activate.bat

# Si usas PowerShell:
venv\Scripts\Activate.ps1
```
*(Sabrás que está activo porque verás un `(venv)` al inicio de la línea en tu consola).*

### Paso 4: Instalar Bibliotecas de Python con pip
Todas las dependencias necesarias para los scripts de análisis y graficación (como `pandas`, `matplotlib`, `seaborn`, `numpy`, etc.) han sido declaradas en el archivo `properties.txt`. Instálalas ejecutando:
```bash
pip install -r properties.txt
```

### Paso 5: Ejecutar el Sistema
Una vez compilado el ejecutable y con las dependencias de Python listas, puedes inicializar la orquestación del simulador ejecutando el script principal:
```bash
python app.py
```
*(Nota: Si utilizas otro script principal de Python para las simulaciones como `generate_input.py` o `visualize_results.py`, siéntete libre de ejecutarlos según sea necesario).*