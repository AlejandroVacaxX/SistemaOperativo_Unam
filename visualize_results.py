import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# script para leer los resultados de la simulacion y generar graficas de rendimiento
def analizar_resultados(archivo_csv):
    try:
        # cargamos los datos usando pandas para facilitar el manejo de tablas
        df = pd.read_csv(archivo_csv)
        
        # si hay demasiados procesos solo mostramos los primeros 25 para que sea legible
        if len(df) > 25:
            df = df.head(25)
        
        # configuramos el estilo visual de las graficas
        sns.set_theme(style="whitegrid")
        
        # creamos una grafica de barras para ver el tiempo de rafaga por cada proceso
        plt.figure(figsize=(10, 6))
        grafica = sns.barplot(x='pid', y='burst_time', data=df, hue='pid', palette='viridis', legend=False)
        plt.title('tiempo de rafaga por proceso (burst time)')
        plt.xlabel('id del proceso (pid)')
        plt.ylabel('tiempo (unidades)')
        
        # guardamos la grafica en un archivo de imagen
        plt.savefig('grafica_rendimiento.png')
        
    except Exception as e:
        # si ocurre un error al leer o graficar lo ignoramos silenciosamente por ahora
        pass

if __name__ == "__main__":
    analizar_resultados('output.csv')
