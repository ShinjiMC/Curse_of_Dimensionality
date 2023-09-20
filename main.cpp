#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <Windows.h>

using namespace std;

#define numPoints 100

std::vector<std::vector<double>> GetPoints(int d){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::vector<std::vector<double>> puntos;
    for (int n = 0; n < numPoints; ++n){
        std::vector<double> point(d);
        for (int i = 0; i < d; ++i) {
            point[i] = dis(gen);
        }
        puntos.push_back(point);
    }
    return puntos;
}

double GetEuclideanDistance(const std::vector<double>& A, const std::vector<double>& B) {
    double result = 0;
    for (int i = 0; i < A.size(); i++) {
        result = result + pow((A[i] - B[i]), 2);
    }
    return sqrt(result);
}

std::vector<double> GetDistances(const std::vector<std::vector<double>>& points){
    std::vector<double> distances;
    for (int i = 0; i < numPoints; i++) {
        for (int j = i + 1; j < numPoints; j++) {
            distances.push_back(GetEuclideanDistance(points[i],points[j]));
        }
    }
    return distances;
}

void LoadFile(const std::vector<double>& distances, const int& dim){
    std::ofstream outputFile("Histogram/distances",std::ios::trunc);
    if (!outputFile.is_open()) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return;
    }
    outputFile << dim << " ";
    for (size_t i = 0; i < distances.size(); ++i) {
        outputFile << distances[i] << " ";
    }
    outputFile.close();
}

int ChooseD() {
    int opcion;
    int valorSeleccionado = 0;
    std::cout << "The Curse of Dimensionality" << std::endl;
    while (true) {
        std::cout << "Choose an option:" << std::endl;
        std::cout << "1. 2 dimensions" << std::endl;
        std::cout << "2. 10 dimensions" << std::endl;
        std::cout << "3. 50 dimensions" << std::endl;
        std::cout << "4. 100 dimensions" << std::endl;
        std::cout << "5. 500 dimensions" << std::endl;
        std::cout << "6. 1000 dimensions" << std::endl;
        std::cout << "7. 2000 dimensions" << std::endl;
        std::cout << "8. 5000 dimensions" << std::endl;
        std::cout << "9. Exit" << std::endl;

        std::string input;
        std::cout << "Input: ";
        std::cin >> input;

        if (input == "9") {
            std::cout << "Exiting the program." << std::endl;
            break;
        }

        try {
            opcion = std::stoi(input);

            switch (opcion) {
                case 1:
                    valorSeleccionado = 2;
                    return valorSeleccionado;
                case 2:
                    valorSeleccionado = 10;
                    return valorSeleccionado;
                case 3:
                    valorSeleccionado = 50;
                    return valorSeleccionado;
                case 4:
                    valorSeleccionado = 100;
                    return valorSeleccionado;
                case 5:
                    valorSeleccionado = 500;
                    return valorSeleccionado;
                case 6:
                    valorSeleccionado = 1000;
                    return valorSeleccionado;
                case 7:
                    valorSeleccionado = 2000;
                    return valorSeleccionado;
                case 8:
                    valorSeleccionado = 5000;
                    return valorSeleccionado;
                default:
                    std::cout << "Invalid option. Enter a number from 1 to 8 or 9 to exit." << std::endl;
                    continue;
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input. Enter a number from 1 to 8 or 9 to exit." << std::endl;
        }
    }
    return valorSeleccionado;
}


int main(){
    int d = ChooseD();
    if ( d!=0 ) {
        std::vector<double> distances = GetDistances(GetPoints(d));
        LoadFile(distances,d);
        int result = std::system(".\\Histogram\\Histogram.exe");
        if (result != 0) {
            std::cerr << "Error al ejecutar el Ploteo en GO." << std::endl;
        }
        std::remove(".\\Histogram\\distances");
        int results = std::system(".\\histogram.png");
        if (results != 0) {
            std::cerr << "Error al abrir la imagen." << std::endl;
        }
    }
    return 0;
}