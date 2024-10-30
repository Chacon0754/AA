import ctypes
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Cargar la biblioteca DLL en Python
bubblesort = ctypes.CDLL('P3\\bubbleSortExport.dll')

# Configurar los tipos de argumentos y retorno para las funciones
bubblesort.readFile.argtypes = [ctypes.c_char_p]
bubblesort.readFile.restype = None

bubblesort.bubbleSortStep.argtypes = []
bubblesort.bubbleSortStep.restype = None

bubblesort.getTotalElements.argtypes = []
bubblesort.getTotalElements.restype = ctypes.c_int

bubblesort.getOriginalArray.argtypes = []
bubblesort.getOriginalArray.restype = ctypes.POINTER(ctypes.c_int)

# Leer el archivo usando la función C
filename = b"C:\\Users\\chaco\\OneDrive\\Documentos\\ICC\\Semestre 2024-B\\AA\\AA\\P3\\averageCase.txt"
bubblesort.readFile(filename)

# Obtener el número de elementos y el arreglo original desde C
total_elements = bubblesort.getTotalElements()
original_array = bubblesort.getOriginalArray()

# Convertir el puntero a un arreglo de Python para la animación
def get_array_from_pointer(pointer, length):
    return [pointer[i] for i in range(length)]

# Definir la función que muestra el array en el gráfico
def update_plot(frame):
    # Llamar a bubbleSortStep de C para hacer un paso del ordenamiento
    bubblesort.bubbleSortStep()

    # Mostrar el array actualizado después del paso de Bubble Sort
    updated_values = get_array_from_pointer(original_array, total_elements)
    for rect, val in zip(rects, updated_values):
        rect.set_height(val)

# Configurar la gráfica inicial
fig, ax = plt.subplots()
rects = plt.bar(range(total_elements), get_array_from_pointer(original_array, total_elements), align="edge")
ax.set_xlim(0, total_elements)
ax.set_ylim(0, int(1.1 * max(get_array_from_pointer(original_array, total_elements))))

# Crear la animación
anim = animation.FuncAnimation(fig, update_plot, frames=range(total_elements**2), repeat=False, blit=False)
plt.show()
