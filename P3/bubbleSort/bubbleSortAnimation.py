#  Elaboracion: 29/10/2024
#  BubbleSort
#  Autores:
#  Martin Eduardo Chacon Orduño - 351840
#  Carlos Esteban Barragán Bernal - 359299
#  Luz Mariam Garcia Castillo - 348409
#  Leonardo Franco Bulkley - 377288

import matplotlib.pyplot as plt
import matplotlib.animation as animation
import sys
import os 

# Obtener la ruta del directorio donde se encuentra el ejecutable
def obtener_ruta_base():
    if getattr(sys, 'frozen', False):
        # Si se ejecuta como un ejecutable creado por PyInstaller
        return sys._MEIPASS
    else:
        # Si se ejecuta como un script de Python
        return os.path.dirname(os.path.abspath(__file__))

# Leer los primeros 50 elementos del archivo averageCase.txt
def leer_datos_archivo(nombre_archivo, num_elementos=50):
    ruta_base = obtener_ruta_base()
    ruta_archivo = os.path.join(ruta_base, nombre_archivo)
    try:
        with open(ruta_archivo, 'r') as archivo:
            datos = [int(linea.strip()) for linea in archivo.readlines()[:num_elementos]]
        return datos
    except FileNotFoundError:
        print(f"No se pudo abrir el archivo {nombre_archivo}")
        sys.exit(1)

# Algoritmo Bubble Sort con animación
def bubble_sort_animado(datos):
    import copy  
    fig, ax = plt.subplots()
    barra_rects = ax.bar(range(len(datos)), datos, align="edge")
    ax.set_xlim(0, len(datos))
    ax.set_ylim(0, int(1.1 * max(datos)))
    titulo = ax.text(0.5, 1.05, "",
                    bbox={'facecolor': 'w', 'alpha': 0.5, 'pad': 5},
                    transform=ax.transAxes, ha="center")

    contador_comparaciones = 0
    contador_intercambios = 0
    n = len(datos)
    i = 0
    counter = n  
    frames = []

    # Implementación del algoritmo Bubble Sort 
    while i < n and counter != 0:
        counter = 0
        j = 0
        while j < n - 1 - i:
            contador_comparaciones += 1
            frames.append((copy.deepcopy(datos), contador_comparaciones, contador_intercambios, j, j + 1))
            if datos[j] > datos[j + 1]:
                datos[j], datos[j + 1] = datos[j + 1], datos[j]
                contador_intercambios += 1
                counter += 1
                frames.append((copy.deepcopy(datos), contador_comparaciones, contador_intercambios, j, j + 1))
            j += 1
        if counter == 0:
            break
        i += 1

    def actualizar_barras(frame):
        datos_snapshot, comparaciones, intercambios, idx1, idx2 = frame
        for rect, val in zip(barra_rects, datos_snapshot):
            rect.set_height(val)
            rect.set_color('blue')
        # Resaltar las barras comparadas
        if idx1 < len(barra_rects) and idx2 < len(barra_rects):
            barra_rects[idx1].set_color('red')
            barra_rects[idx2].set_color('red')
        titulo.set_text(f"Comparaciones: {comparaciones} - Intercambios: {intercambios}")

    anim = animation.FuncAnimation(fig, actualizar_barras, frames=frames, interval=50, repeat=False)
    plt.show()

    print(f"Total de comparaciones: {contador_comparaciones}")
    print(f"Total de intercambios: {contador_intercambios}")

if __name__ == "__main__":
    nombre_archivo = "averageCase.txt"
    datos = leer_datos_archivo(nombre_archivo)
    bubble_sort_animado(datos)
