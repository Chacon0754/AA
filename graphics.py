# Autores:  
# Martin Eduardo Chacon Orduño - 351840
# Carlos Esteban Barragán Bernal - 359299
# Luz Mariam Garcia Castillo
# Leonardo Franco Bulkley


# Para que les funcione necesitan instalar la libreria matplotlib
# se instala con el comando pip install matplotlib
import matplotlib.pyplot as plt

plt.style.use('seaborn-v0_8-dark')

sizes = [100, 1000, 10000, 100000, 1000000]
timesRange1 = [0.000000, 0.004000, 0.599000, 45.324000, 2806.785000]
timesRange2 = [0.000000, 0.002000, 0.304000, 22.488000, 2173.006000]
timesRange3 = [0.000000, 0.000000, 0.000000, 0.000000, 0.002000]

plt.plot(sizes, timesRange1, label = 'Range 1', marker = 'o')
plt.plot(sizes, timesRange2, label = 'Range 2', marker = 'o')
plt.plot(sizes, timesRange3, label = 'Range 3', marker = 'o')
# print(plt.style.available)


plt.title("Execution time with variable array sizes")
plt.xlabel('Array size')
plt.ylabel('Execution time (seconds)')

plt.legend()
plt.grid(True)
plt.show()
