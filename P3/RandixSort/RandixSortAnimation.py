#  Elaboracion: 01/11/2024
# RandixSort
#  Autores:
# Martin Eduardo Chacon Orduño - 351840
# Carlos Esteban Barragán Bernal - 359299
# Luz Mariam Garcia Castillo - 348409
# Leonardo Franco Bulkley - 377288
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


def obtainMaximo(data):
    return max(data)


def countingSortAnimation(data, n, digit, frames, exchanges):
    final = [0] * n
    count = [0] * 10

    # Cuenta la ocurrencia de cada dígito
    for i in range(n):
        count[(data[i] // digit) % 10] += 1

    # Modifica count[i] para tener la posición real en final[]
    for i in range(1, 10):
        count[i] += count[i - 1]

    # Construye el arreglo de salida
    for i in range(n - 1, -1, -1):
        final[count[(data[i] // digit) % 10] - 1] = data[i]
        count[(data[i] // digit) % 10] -= 1
        exchanges += 1
        frames.append((copy.deepcopy(final), exchanges, i, None))

    # Copia los elementos ordenados al arreglo original
    for i in range(n):
        data[i] = final[i]
        exchanges += 1
        frames.append((copy.deepcopy(data), exchanges, i, None))

    return exchanges


def radixSortAnimation(data):
    frames = []
    exchanges = 0

    max_val = obtainMaximo(data)
    n = len(data)

    digit = 1
    while max_val // digit > 0:
        exchanges = countingSortAnimation(data, n, digit, frames, exchanges)
        digit *= 10

    return frames, exchanges


def animateRadixSort(data):
    frames, exchanges = radixSortAnimation(data)

    figure, ax = plt.subplots()
    bars = ax.bar(range(len(data)), data, align='edge')
    ax.set_xlim(0, len(data))
    ax.set_ylim(0, int(1.1 * max(data)))
    title = ax.text(0.5, 1.05, "", bbox={'facecolor': 'w', 'alpha': 0.5, 'pad': 5}, transform=ax.transAxes, ha="center")

    def updateBars(frame):
        snapshotData, exchanges, idx1, _ = frame
        for rectangle, value in zip(bars, snapshotData):
            rectangle.set_height(value)
            rectangle.set_color('blue')

        if idx1 is not None and idx1 < len(bars):
            bars[idx1].set_color('red')

        title.set_text(f"Intercambios: {exchanges}")

    anim = animation.FuncAnimation(figure, updateBars, frames=frames, interval=50, repeat=False)
    plt.show()


if __name__ == "__main__":
    filename = "averageCase.txt"
    data = readFile(filename)
    animateRadixSort(data)
