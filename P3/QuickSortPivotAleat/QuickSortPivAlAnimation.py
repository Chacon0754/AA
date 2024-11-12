#  Elaboracion: 11/11/2024
#  QuickSort
#  Autores:
#  Martin Eduardo Chacon Orduño - 351840
#  Carlos Esteban Barragán Bernal - 359299
#  Luz Mariam Garcia Castillo - 348409
#  Leonardo Franco Bulkley - 377288
#  se debe tener instalado matplotlib para que funcione la animacion
# Tambien debe estar el archivo averageCase.txt en la misma carpeta
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import copy
import sys
import os
import random

def obtainBasePath():
    if getattr(sys, 'frozen', False):
        return sys._MEIPASS
    else:
        return os.path.dirname(os.path.abspath(__file__))

def readFile(filename, elementnumber=50):
    basePath = obtainBasePath()
    filePath = os.path.join(basePath, filename)
    try:
        with open(filePath, 'r') as file:
            data = [int(line.strip()) for line in file.readlines()[:elementnumber]]
        return data
    except FileNotFoundError:
        print(f"No se pudo abrir el archivo {filename}")
        sys.exit(1)

def quickSortAnimation(data):
    figure, ax = plt.subplots()
    bars = ax.bar(range(len(data)), data, align='edge')
    ax.set_xlim(0, len(data))
    ax.set_ylim(0, int(1.1 * max(data)))
    title = ax.text(0.5, 1.05, "", bbox={'facecolor': 'w', 'alpha': 0.5, 'pad': 5}, transform=ax.transAxes, ha="center")
    comparisons = 0
    exchanges = 0
    frames = []

    def quickSort(data, low, high):
        nonlocal comparisons, exchanges
        if low < high:
            pi = partition(data, low, high)
            quickSort(data, low, pi - 1)
            quickSort(data, pi + 1, high)

    def partition(data, low, high):
        nonlocal comparisons, exchanges
        
        # Selección de pivote aleatorio
        pivotIndex = random.randint(low, high)
        pivot = data[pivotIndex]
        
        # Intercambiar el pivote con el último elemento para facilitar la partición
        data[pivotIndex], data[high] = data[high], data[pivotIndex]
        exchanges += 1
        frames.append((copy.deepcopy(data), comparisons, exchanges, pivotIndex, high))  # Agregar estado tras intercambio

        i = low - 1
        for j in range(low, high):
            comparisons += 1
            frames.append((copy.deepcopy(data), comparisons, exchanges, j, high))  # Agregar estado del arreglo
            if data[j] < pivot:
                i += 1
                data[i], data[j] = data[j], data[i]
                exchanges += 1
                frames.append((copy.deepcopy(data), comparisons, exchanges, i, j))  # Agregar estado tras intercambio

        data[i + 1], data[high] = data[high], data[i + 1]
        exchanges += 1
        frames.append((copy.deepcopy(data), comparisons, exchanges, i + 1, high))  # Agregar estado tras intercambio
        return i + 1

    quickSort(data, 0, len(data) - 1)
    print(f"Total de comparaciones: {comparisons}")
    print(f"Total de intercambios: {exchanges}")

    def updateBars(frame):
        snapshotData, comparisons, exchanges, idx1, idx2 = frame
        for rectangle, value in zip(bars, snapshotData):
            rectangle.set_height(value)
            rectangle.set_color('blue')

        if idx1 < len(bars):
            bars[idx1].set_color('red')
        if idx2 < len(bars):
            bars[idx2].set_color('green')

        title.set_text(f"Comparaciones: {comparisons} - Intercambios: {exchanges}")

    anim = animation.FuncAnimation(figure, updateBars, frames=frames, interval=50, repeat=False)
    plt.show()

if __name__ == "__main__":
    filename = "averageCase.txt"
    data = readFile(filename)
    quickSortAnimation(data)
