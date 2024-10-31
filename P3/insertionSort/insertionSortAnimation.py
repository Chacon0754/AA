#  Elaboracion: 31/10/2024
#  InsertionSort
#  Autores:
#  Martin Eduardo Chacon Orduño - 351840
#  Carlos Esteban Barragán Bernal - 359299
#  Luz Mariam Garcia Castillo - 348409
#  Leonardo Franco Bulkley - 377288

import matplotlib.pyplot as plt
import matplotlib.animation as animation
import copy
import sys
import os

def obtainBasePath():
    if getattr(sys, 'frozen', False):
        return sys._MEIPASS
    else:
        return os.path.dirname(os.path.abspath(__file__))
    
def readFile(filename, elementsNumber = 50):
    basePath = obtainBasePath()
    filePath = os.path.join(basePath, filename)
    try:
        with open(filePath, 'r') as file:
            data = [int(line.strip()) for line in file.readlines()[:elementsNumber]]
        return data
    except FileNotFoundError:
        print(f"No se pudo abrir el archivo {filename}")
        sys.exit(1)

def insertionSortAnimation(data):
    figure, ax = plt.subplots()
    bars = ax.bar(range(len(data)), data, align="edge")
    ax.set_xlim(0, len(data))
    ax.set_ylim(0, int(1.1 * max(data)))
    title = ax.text(0.5, 1.05, "",
                    bbox={'facecolor': 'w', 'alpha': 0.5, 'pad': 5},
                    transform=ax.transAxes, ha="center")
    comparisons = 0
    exchanges = 0
    frames = []

    for i in range(len(data)):
        key = data[i]
        j = i - 1

        frames.append((copy.deepcopy(data), comparisons, exchanges, i, j))

        while j >= 0 and data[j] > key:
            comparisons += 1
            data[j + 1] = data[j]
            exchanges += 1
            frames.append((copy.deepcopy(data), comparisons, exchanges, j, j + 1))
            j -= 1

        data[j + 1] = key
        exchanges += 1
        frames.append((copy.deepcopy(data), comparisons, exchanges, j + 1, i))

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

    anim = animation.FuncAnimation(figure, updateBars, frames = frames, interval = 50, repeat = False)
    plt.show()

    print(f"Total de comparaciones: {comparisons}")
    print(f"Total de intercambios: {exchanges}")

if __name__ == "__main__":
    filename = "averageCase.txt"
    data = readFile(filename)
    insertionSortAnimation(data)