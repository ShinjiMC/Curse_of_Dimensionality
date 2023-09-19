#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>

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

void LoadFile(const std::vector<double>& distances){
    std::ofstream outputFile("Histogram/distances",std::ios::trunc);
    if (!outputFile.is_open()) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return;
    }
    for (size_t i = 0; i < distances.size(); ++i) {
        outputFile << distances[i] << " ";
    }
    outputFile.close();
}

int main(){
    int d = 100;
    std::vector<double> distances = GetDistances(GetPoints(d));
    LoadFile(distances);
    /*std::cout << "Distance: " << distances.size() << std::endl;
    std::cout << "Datos de distances:" << std::endl;
    for (size_t i = 0; i < distances.size(); ++i) {
        std::cout << distances[i] << "\t";
    }*/
    int result = std::system(".\\Histogram\\Histogram.exe");

    if (result != 0) {
        std::cerr << "Error al ejecutar el Ploteo en GO." << std::endl;
    }
    return 0;
}