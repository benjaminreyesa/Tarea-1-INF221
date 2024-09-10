#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace chrono;

// ----------------Función para multiplicar matrices con el algoritmo cúbico tradicional -------------
vector<vector<int>> multiplyTraditional(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    int m = B[0].size();
    int p = A[0].size();
    
    vector<vector<int>> C(n, vector<int>(m, 0)); // Matriz de resultado inicializada en 0

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < p; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Función para transponer una matriz
vector<vector<int>> transpose(const vector<vector<int>>& B) {
    int n = B.size();
    int m = B[0].size();
    vector<vector<int>> B_T(m, vector<int>(n, 0));  // Matriz transpuesta

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            B_T[j][i] = B[i][j];
        }
    }
    return B_T;
}

// ---------------- Función para multiplicar matrices con el algoritmo cúbico optimizado -----------------
vector<vector<int>> multiplyOptimizedTranspose(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    int m = B[0].size();
    int p = A[0].size();
    
    vector<vector<int>> B_T = transpose(B);  // Transponemos la segunda matriz
    vector<vector<int>> C(n, vector<int>(m, 0));  // Matriz de resultado inicializada en 0

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < p; k++) {
                C[i][j] += A[i][k] * B_T[j][k];  // Notar que usamos la transpuesta B_T
            }
        }
    }
    return C;
}

// Función auxiliar para sumar matrices
vector<vector<int>> addMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

// Función auxiliar para restar matrices
vector<vector<int>> subtractMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}


// ------------------- Algoritmo de Strassen -------------------
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    if (n == 1) {  // Caso base: multiplicación de matrices 1x1
        C[0][0] = A[0][0] * B[0][0];
    } else {
        int newSize = n / 2;
        vector<vector<int>> A11(newSize, vector<int>(newSize)), A12(newSize, vector<int>(newSize)),
                            A21(newSize, vector<int>(newSize)), A22(newSize, vector<int>(newSize)),
                            B11(newSize, vector<int>(newSize)), B12(newSize, vector<int>(newSize)),
                            B21(newSize, vector<int>(newSize)), B22(newSize, vector<int>(newSize));

        // Dividir las matrices en submatrices
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + newSize];
                A21[i][j] = A[i + newSize][j];
                A22[i][j] = A[i + newSize][j + newSize];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + newSize];
                B21[i][j] = B[i + newSize][j];
                B22[i][j] = B[i + newSize][j + newSize];
            }
        }

        // Calcular las 7 multiplicaciones de Strassen
        vector<vector<int>> M1 = strassen(addMatrix(A11, A22), addMatrix(B11, B22));
        vector<vector<int>> M2 = strassen(addMatrix(A21, A22), B11);
        vector<vector<int>> M3 = strassen(A11, subtractMatrix(B12, B22));
        vector<vector<int>> M4 = strassen(A22, subtractMatrix(B21, B11));
        vector<vector<int>> M5 = strassen(addMatrix(A11, A12), B22);
        vector<vector<int>> M6 = strassen(subtractMatrix(A21, A11), addMatrix(B11, B12));
        vector<vector<int>> M7 = strassen(subtractMatrix(A12, A22), addMatrix(B21, B22));

        // Combinar los resultados para obtener C
        vector<vector<int>> C11 = addMatrix(subtractMatrix(addMatrix(M1, M4), M5), M7);
        vector<vector<int>> C12 = addMatrix(M3, M5);
        vector<vector<int>> C21 = addMatrix(M2, M4);
        vector<vector<int>> C22 = addMatrix(subtractMatrix(addMatrix(M1, M3), M2), M6);

        // Unir los resultados
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                C[i][j] = C11[i][j];
                C[i][j + newSize] = C12[i][j];
                C[i + newSize][j] = C21[i][j];
                C[i + newSize][j + newSize] = C22[i][j];
            }
        }
    }
    return C;
}

//--------------------------------------------------------------------------------------------------------

// Función para generar una matriz cuadrada de tamaño n x n con valores aleatorios
vector<vector<int>> generateRandomMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    srand(time(0));  // Semilla aleatoria basada en el tiempo

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = rand() % 100;  // Generar números entre 0 y 99
        }
    }
    return matrix;
}

// Función para imprimir una matriz
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

// Genera matriz no cuadrada
vector<vector<int>> generateRandomMatrixNonSquare(int rows, int cols) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    srand(time(0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % 100;
        }
    }
    return matrix;
}
//----------------------MAIN-------------------------

int main() {
    //Caso 0: Matrices Cuadradas
    int n = 1200;  // Tamaño de la matriz
    vector<vector<int>> A = generateRandomMatrix(n);
    vector<vector<int>> B = generateRandomMatrix(n);
    
    //Caso 1: Matrices de distintas dimensiones
    //int n = 1000;  // Número de filas de A
    //int p = 600;   // Número de columnas de A y filas de B
    //int m = 800;   // Número de columnas de B
    //vector<vector<int>> A = generateRandomMatrixNonSquare(n, p);  // Generar matriz A de tamaño n x p
    //vector<vector<int>> B = generateRandomMatrixNonSquare(p, m);   
    // Caso 3: Matrices no cuadradas y una transpuesta
    //int n = 800;  // Filas de A
    //int p = 400;  // Columnas de A y filas de B
    //int m = 600;  // Columnas de B

    //vector<vector<int>> A = generateRandomMatrixNonSquare(n, p);     // Generar matriz A de tamaño n x p
    //vector<vector<int>> B = generateRandomMatrixNonSquare(p, m);     // Generar matriz B de tamaño p x m
    //vector<vector<int>> B_T = generateTransposedMatrix(B);           // Generar matriz transpuesta de B


    // Medir el tiempo de multiplicación con el algoritmo tradicional
    auto start = high_resolution_clock::now();
    vector<vector<int>> C1 = multiplyTraditional(A, B);
    auto end = high_resolution_clock::now();
    duration<double> duration_traditional = end - start;
    cout << "Algoritmo cubico tradicional tomo " << duration_traditional.count() << " segundos." << endl;

    // Medir el tiempo de multiplicación con el algoritmo optimizado
    start = high_resolution_clock::now();
    vector<vector<int>> C2 = multiplyOptimizedTranspose(A, B);
    end = high_resolution_clock::now();
    duration<double> duration_optimized = end - start;
    cout << "Algoritmo cubico optimizado tomo " << duration_optimized.count() << " segundos." << endl;

    // Medir el tiempo de multiplicación con el algoritmo de Strassen
    start = high_resolution_clock::now();
    vector<vector<int>> C3 = strassen(A, B);
    end = high_resolution_clock::now();
    duration<double> duration_strassen = end - start;
    cout << "Algoritmo de Strassen tomo " << duration_strassen.count() << " segundos." << endl;

    return 0;
}