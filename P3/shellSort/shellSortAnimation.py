#  Elaboracion: 06/11/2024
#  Shell sort
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

def shellSortAnimation(data):
    figure, ax = plt.subplots()
    bars = ax.bar(range(len(data)), data, align='edge', color='blue')
    ax.set_xlim(0, len(data))
    ax.set_ylim(0, int(1.1 * max(data)))
    ax.set_xlabel("Índice")
    ax.set_ylabel("Valor")
    title = ax.text(0.5, 1.05, "", bbox={'facecolor': 'w', 'alpha': 0.5, 'pad': 5},
                    transform=ax.transAxes, ha="center")

    comparisons = 0
    exchanges = 0
    frames = []

    n = len(data)
    gap = n // 2

    while gap > 0:
        frames.append((copy.deepcopy(data), comparisons, exchanges, -1, -1, gap))
        for i in range(gap, n):
            temp = data[i]
            j = i

            frames.append((copy.deepcopy(data), comparisons, exchanges, j, j - gap, gap))

            while j >= gap and data[j - gap] > temp:
                comparisons += 1
                data[j] = data[j - gap]
                exchanges += 1
                frames.append((copy.deepcopy(data), comparisons, exchanges, j, j - gap, gap))
                j -= gap

            if j >= gap:
                comparisons += 1

            data[j] = temp
            exchanges += 1
            frames.append((copy.deepcopy(data), comparisons, exchanges, j, i, gap))
        gap //= 2

    print(f"Total de comparaciones: {comparisons}")
    print(f"Total de intercambios: {exchanges}")

    def updateBars(frame):
        snapshotData, comparisons, exchanges, idx1, idx2, gap = frame
        for rectangle, value in zip(bars, snapshotData):
            rectangle.set_height(value)
            rectangle.set_color('blue')

        if 0 <= idx1 < len(bars):
            bars[idx1].set_color('red')
        if 0 <= idx2 < len(bars):
            bars[idx2].set_color('green')

        title.set_text(f"Gap: {gap} - Comparaciones: {comparisons} - Intercambios: {exchanges}")

    anim = animation.FuncAnimation(figure, updateBars, frames=frames, interval=50, repeat=False)
    plt.show()

    print(f"Total de comparaciones: {comparisons}")
    print(f"Total de intercambios: {exchanges}")


if __name__ == "__main__":
    filename = "averageCase.txt"
    data = readFile(filename)
    shellSortAnimation(data)
