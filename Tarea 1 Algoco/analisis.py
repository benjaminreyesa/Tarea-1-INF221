import pandas as pd
import matplotlib.pyplot as plt

# Tamaños de entrada
input_sizes = [5000, 15000, 30000]

# Datos en milisegundos para cada tipo de vector
data_random = {
    'Algoritmo': ['Merge Sort', 'Quick Sort', 'Selection Sort', 'Función Sort'],
    '5000': [2.992, 0.997, 56.856, 0.998],
    '15000': [9.973, 3.989, 517.65, 2.993],
    '30000': [19.971, 7.014, 2000.87, 6.981]
}

data_asc = {
    'Algoritmo': ['Merge Sort', 'Quick Sort', 'Selection Sort', 'Función Sort'],
    '5000': [2.991, 177.551, 60.864, 0.998],
    '15000': [8.976, 1554.43, 506.68, 1.995],
    '30000': [16.955, 6178.32, 2005.4, 3.989]
}

data_desc = {
    'Algoritmo': ['Merge Sort', 'Quick Sort', 'Selection Sort', 'Función Sort'],
    '5000': [2.022, 101.728, 55.887, 1.0],
    '15000': [7.979, 919.256, 502.724, 0.998],
    '30000': [16.954, 3624.95, 2003.53, 3.989]
}

data_partial = {
    'Algoritmo': ['Merge Sort', 'Quick Sort', 'Selection Sort', 'Función Sort'],
    '5000': [2.992, 30.916, 56.879, 0.998],
    '15000': [8.976, 134.639, 511.665, 7.015],
    '30000': [16.979, 305.156, 1997.34, 9.973]
}

# Convertir a DataFrames para facilitar los gráficos
df_random = pd.DataFrame(data_random)
df_asc = pd.DataFrame(data_asc)
df_desc = pd.DataFrame(data_desc)
df_partial = pd.DataFrame(data_partial)

# Función para graficar
def plot_graph(df, title):
    plt.figure(figsize=(10, 6))
    for index, row in df.iterrows():
        plt.plot(input_sizes, [row['5000'], row['15000'], row['30000']], label=row['Algoritmo'], marker='o')

    plt.xlabel('Tamaño de la entrada')
    plt.ylabel('Tiempo de ejecución (milisegundos)')
    plt.title(title)
    plt.legend()
    plt.grid(True)
    plt.savefig(f"{title.replace(' ', '_')}.png")  # Guardar el gráfico como imagen PNG
    plt.show()

# Graficar para cada caso
plot_graph(df_random, 'Comparación Algoritmos - Números Aleatorios')
plot_graph(df_asc, 'Comparación Algoritmos - Números Ascendentes')
plot_graph(df_desc, 'Comparación Algoritmos - Números Descendentes')
plot_graph(df_partial, 'Comparación Algoritmos - Números Parcialmente Ordenados')

##-----------------------------------------------------------------------------------


# Convertir los diccionarios a DataFrames
df_random = pd.DataFrame(data_random)
df_asc = pd.DataFrame(data_asc)
df_desc = pd.DataFrame(data_desc)
df_partial = pd.DataFrame(data_partial)

# Función para mostrar la tabla y guardarla como imagen
def plot_table(df, title):
    fig, ax = plt.subplots(figsize=(8, 4))  # Tamaño de la imagen
    ax.axis('tight')
    ax.axis('off')
    table = ax.table(cellText=df.values, colLabels=df.columns, cellLoc='center', loc='center')
    table.auto_set_font_size(False)
    table.set_fontsize(10)
    table.scale(1.2, 1.2)  # Ajustar el tamaño de la tabla
    plt.title(title)
    
    # Guardar la tabla como imagen PNG
    plt.savefig(f"{title.replace(' ', '_')}.png")
    plt.show()

# Crear y guardar tablas para cada caso
plot_table(df_random, 'Tabla - Números Aleatorios')
plot_table(df_asc, 'Tabla - Números Ascendentes')
plot_table(df_desc, 'Tabla - Números Descendentes')
plot_table(df_partial, 'Tabla - Números Parcialmente Ordenados')

#---------------------ANALIZANDO MATRICES--------------------------------
# ------------------- Datos para matrices cuadradas -------------------
data_cuadradas = {
    'Tamaño de matriz': [10, 50, 200, 500, 700, 1000, 1200],
    'Cúbico Tradicional': [0, 0.001994, 0.111702, 1.75948, 5.34317, 17.7205, 27.3481],
    'Cúbico Optimizado': [0, 0.001994, 0.110736, 1.66857, 4.65701, 13.4876, 22.7715],
    'Strassen': [0.000997, 0.062833, 3.01542, 21.2565, 144.236, 153.83, 972.413]
}
# ------------------- Datos para matrices NO cuadradas -------------------
data_no_cuadradas = {
    'Dimensiones de Matriz': ['1000x600 * 600x800', '800x400 * 400x600', '800x400 * 400x600 (B Transpuesta)'],
    'Cúbico Tradicional': [7.14787, 2.66237, 1.73855],
    'Cúbico Optimizado': [6.33805, 2.5126, 1.69772],
    'Strassen': ['Falla', 'Falla', 'Falla']
}

# Crear DataFrames
df_cuadradas = pd.DataFrame(data_cuadradas)
df_no_cuadradas = pd.DataFrame(data_no_cuadradas)

# ------------------- Generar gráficos -------------------

# Gráfico para matrices cuadradas
plt.figure(figsize=(10, 6))
plt.plot(df_cuadradas['Tamaño de matriz'], df_cuadradas['Cúbico Tradicional'], label='Cúbico Tradicional', marker='o')
plt.plot(df_cuadradas['Tamaño de matriz'], df_cuadradas['Cúbico Optimizado'], label='Cúbico Optimizado', marker='o')
plt.plot(df_cuadradas['Tamaño de matriz'], df_cuadradas['Strassen'], label='Strassen', marker='o')
plt.title('Tiempo de multiplicación (matrices cuadradas)')
plt.xlabel('Tamaño de matriz (nxn)')
plt.ylabel('Tiempo (segundos)')
plt.legend()
plt.grid(True)
plt.savefig('grafico_matrices_cuadradas.png')
plt.show()

# Gráfico para matrices no cuadradas
plt.figure(figsize=(10, 6))
plt.plot(df_no_cuadradas['Dimensiones de Matriz'], df_no_cuadradas['Cúbico Tradicional'], label='Cúbico Tradicional', marker='o')
plt.plot(df_no_cuadradas['Dimensiones de Matriz'], df_no_cuadradas['Cúbico Optimizado'], label='Cúbico Optimizado', marker='o')
plt.title('Tiempo de multiplicación (matrices no cuadradas)')
plt.xlabel('Dimensiones de Matriz')
plt.ylabel('Tiempo (segundos)')
plt.legend()
plt.grid(True)
plt.savefig('grafico_matrices_no_cuadradas.png')
plt.show()

# ------------------- Generar tablas -------------------

# Tabla para matrices cuadradas
def plot_table(df, title):
    fig, ax = plt.subplots(figsize=(10, 4))  # Ajuste del tamaño de la imagen
    ax.axis('tight')
    ax.axis('off')
    table = ax.table(cellText=df.values, colLabels=df.columns, cellLoc='center', loc='center')
    table.auto_set_font_size(False)
    table.set_fontsize(10)
    table.scale(1.2, 1.2)  # Ajustar el tamaño de la tabla
    plt.title(title)
    plt.savefig(f"{title.replace(' ', '_')}.png")
    plt.show()

# Crear y guardar tablas
plot_table(df_cuadradas, 'Tabla - Tiempos Matrices Cuadradas')
plot_table(df_no_cuadradas, 'Tabla - Tiempos Matrices NO Cuadradas')