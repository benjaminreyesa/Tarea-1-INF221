#include <bits/stdc++.h>
#include <chrono>

using namespace std;

// Función para imprimir un array (vector) en la consola
void printArray(const vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";  // Imprime cada elemento seguido de un espacio
    }
    cout << endl;
}

// ------------------- Merge Sort --------------------
// Función para combinar (merge) dos subarreglos ya ordenados de un array
void merge(vector<int>& arr, int left, int mid, int right) {
    // Dividir el array en dos subarreglos
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crear subarreglos temporales
    vector<int> L(n1), R(n2);

    // Copiar los datos a los subarreglos L[] y R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Inicializar índices para fusionar subarreglos
    int i = 0, j = 0;
    int k = left;  // Índice inicial para la fusión en el array original

    // Combinar los subarreglos hasta que uno de ellos se agote
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes del subarreglo izquierdo (si es que quedan)
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes del subarreglo derecho (si es que quedan)
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función recursiva para implementar el algoritmo Merge Sort
void mergeSort(vector<int>& arr, int left, int right) {
    // Condición de término para la recursión
    if (left >= right) {
        return;
    }
    // Encontrar el punto medio del array
    int mid = left + (right - left) / 2;

    // Llamar recursivamente a mergeSort para las mitades izquierda y derecha
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // Combinar las dos mitades ordenadas
    merge(arr, left, mid, right);
}

// ------------------- Quick Sort --------------------
// Función para dividir el array en dos subarrays, usando un pivote
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // Seleccionar el último elemento como pivote
    int i = low - 1;  // Índice del elemento más pequeño

    // Recorrer el array comparando cada elemento con el pivote
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;  // Si el elemento es menor o igual que el pivote, intercambiar
            swap(arr[i], arr[j]);
        }
    }
    // Colocar el pivote en su posición correcta
    swap(arr[i + 1], arr[high]);
    return i + 1;  // Devolver la posición del pivote
}

// Función recursiva para implementar el algoritmo Quick Sort
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // Encontrar el índice de partición
        int pi = partition(arr, low, high);

        // Ordenar recursivamente los elementos antes y después de la partición
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ------------------- Selection Sort --------------------
// Función para implementar el algoritmo Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();  // Obtener el tamaño del array

    // Mover el límite del subarray no ordenado
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;  // Encontrar el elemento mínimo en el subarray no ordenado
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;  // Actualizar el índice del mínimo si se encuentra uno más pequeño
        }
        // Intercambiar el elemento mínimo con el primer elemento
        swap(arr[min_idx], arr[i]);
    }
}

// ------------------- Main Program --------------------
int main() {
    // Leer los números desde un archivo y almacenarlos en un vector
    ifstream archivo("C:/Users/benja/OneDrive/Escritorio/Tarea 1 Algoco/numeros_aleatorios2.txt");
    vector<int> numeros1;
    int numero1;

    // Verificar si el archivo se abrió correctamente
    if (archivo.is_open()) {
        // Leer cada número del archivo y agregarlo al vector
        while (archivo >> numero1) {
            numeros1.push_back(numero1);
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;  // Salir del programa si no se pudo abrir el archivo
    }

    // Verificar si el vector está vacío
    if (numeros1.empty()) {
        cout << "El archivo está vacío o no se pudo leer correctamente." << endl;
        return 1;
    } else {
        cout << "Archivo leído correctamente. Tamaño: " << numeros1.size() << " elementos." << endl;
    }

    // Hacer una copia del vector original para cada algoritmo
    vector<int> arr_merge = numeros1;
    vector<int> arr_quick = numeros1;
    vector<int> arr_selection = numeros1;
    vector<int> arr_sort = numeros1;

    // Medir el tiempo de Merge Sort
    auto start = chrono::high_resolution_clock::now();
    mergeSort(arr_merge, 0, arr_merge.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion_merge_sort = end - start;
    cout << "Merge Sort tomo " << duracion_merge_sort.count() << " segundos." << endl;

    // Medir el tiempo de Quick Sort
    start = chrono::high_resolution_clock::now();
    quickSort(arr_quick, 0, arr_quick.size() - 1);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion_quick_sort = end - start;
    cout << "Quick Sort tomo " << duracion_quick_sort.count() << " segundos." << endl;

    // Medir el tiempo de Selection Sort
    start = chrono::high_resolution_clock::now();
    selectionSort(arr_selection);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion_selection_sort = end - start;
    cout << "Selection Sort tomo " << duracion_selection_sort.count() << " segundos." << endl;

    // Medir el tiempo de la función nativa de C++ sort
    start = chrono::high_resolution_clock::now();
    sort(arr_sort.begin(), arr_sort.end());
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion_sort = end - start;
    cout << "Funcion Sort tomo " << duracion_sort.count() << " segundos." << endl;

    return 0;
}


