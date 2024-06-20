#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "Grafo.h"
#include "Grafo.cpp"

int main() {
	Grafo<char> grafo;
	
    std::ifstream archivo("arista.txt");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo arista.txt" << std::endl;
        return 1;
    }
    
    int numVertices;
    archivo >> numVertices;
    
    std::vector<char> vOrigen, vDestino;
    std::vector<int> vPeso;
    
    std::string linea;
    getline(archivo, linea);
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        char origen, destino;
        int peso;
        ss >> origen;
        ss.ignore(3); // Ignorar " -> "
        ss >> destino >> peso;

		vOrigen.push_back(origen);
		vDestino.push_back(destino);
		vPeso.push_back(peso);
    }
    archivo.close();
    
    grafo.crearMatriz(numVertices, vOrigen, vDestino, vPeso);
    grafo.imprimir();
    
    std::cout << "Es fuertemente conexo?: " << grafo.esFuertementeConexo() << std::endl;
    
    if (!grafo.esFuertementeConexo()){
    	grafo.obtenerVerticesFuentes();
    	grafo.obtenerVerticesPozos();
	}
	
	char letra;
	//std::cout << "Ingrese vertice a eliminar: ";
	//std::cin >> letra;
	
	//grafo.eliminar(letra);
	grafo.imprimir(); 
	
	char origen, destino;
	std::cout << "Ingrese vertice origen: ";
	std::cin >> origen;
	std::cout << "Ingrese vertice destino: ";
	std::cin >> destino;
	
	int numRuta = grafo.rutaMinima(origen, destino);
	std::cout << "Ruta minima: " << numRuta << std::endl;
	
    return 0;
}


