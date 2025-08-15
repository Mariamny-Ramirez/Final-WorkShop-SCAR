#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime> // Para inicializar el generador de números aleatorios
#include <chrono> // Para medir el tiempo de ejecución
#include <iomanip> // Para dar formato a los números decimales en la salida

#define N 50 //numero de iteraciones
#define MIN_SIZE 2 //Tamaño minimo de las matrices
#define MAX_SIZE 1000 //Tamaño maximo de las matrices
#define MAX_NUM 10000000.0 //valor máximo para los numeros aleatorios

int main() {
    //inicializando el generador de numeros aleatorios con el tiempo actual
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    //Generar un tamaño aleatorio 
    int size = MIN_SIZE + (std::rand() % MAX_SIZE);
    int iterator = 0;
    double time_spent = 0.0;

    // Declaración de las matrices A, B y C de tamaño 'size x size'
    std::vector<std::vector<double>> A(size, std::vector<double>(size));
    std::vector<std::vector<double>> B(size, std::vector<double>(size));
    std::vector<std::vector<double>> C(size, std::vector<double>(size));


    // Repetir la multiplicación N veces para obtener un promedio
    while (iterator++ < N) {
        std::cout << "Running iteration number: " << iterator << std::endl;

        // Inicializar las matrices con valores aleatorios (entre 1 y MAX_NUM)
        for (int i = 0; i < size; ++i){
            for (int j = 0; j < size; ++j){
                A[j][i] = 1 + (static_cast<double>(std::rand()) / RAND_MAX) * MAX_NUM;
                B[j][i] = 1 + (static_cast<double>(std::rand()) / RAND_MAX) * MAX_NUM;
                C[j][i] = 0;
            }
        }

        // Medir tiempo
        auto start = std::chrono::high_resolution_clock::now();

        // Multiplicación de matrices
        // Se usa paralelización con OpenMP sobre el primer bucle (filas de A)
        #pragma omp parallel for
        for (int i = 0; i < size; ++i){
            for (int j = 0; j < size; ++j){
                double sum = 0.0;
                for (int k = 0; k < size; ++k){
                    sum += A[i][k] * B[k][j];
                    }
                C[i][j] = sum;
    }
}


        //Finalizar conteo
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        time_spent += elapsed_seconds.count();
    }


    //Mostrar resultado
    std::cout << "Size of matrices: " << size << std::endl;
    std::cout << "Average running time: " << std::fixed << std::setprecision(6)
              << (time_spent / N) << " seconds\n";

    return 0;
}
