#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "Grafo.h"
#include "Grafo.cpp"

void menu(int &resp);

int main() {
	Grafo<char> grafo;
	
	int resp;
    bool archLoad=false; // Variable para verificar si se ha cargado el archivo
    int numVertices;
    
    std::vector<char> vOrigen, vDestino;
    std::vector<int> vPeso;

    // Bucle principal del programa
    
do {
        menu(resp); // Muestra el menú y obtiene la respuesta del usuario
        switch(resp) {
            case 1: {
                // Cargar archivo
                std::ifstream archivo("arista.txt");
                if (!archivo.is_open()) {
                    std::cerr << "No se pudo abrir el archivo arista.txt" << std::endl;
                    break;
                }

                archivo >> numVertices;
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
                archLoad = true;
                break;
            }
            case 2: {
                // Determinar si el grafo es fuertemente conexo
                if (archLoad) {
                    bool esConexo = grafo.esFuertementeConexo();
                    std::cout << "Es fuertemente conexo?: " << (esConexo ? "Sí" : "No") << std::endl;
                } else {
                    std::cout << "Primero cargue un archivo." << std::endl;
                }
                break;
            }
            case 3: {
                // Determinar si existen nodos fuente y nodos pozo
                if (archLoad) {
                    grafo.obtenerVerticesFuentes();
                    grafo.obtenerVerticesPozos();
                } else {
                    std::cout << "Primero cargue un archivo." << std::endl;
                }
                break;
            }
            case 4: {
                // Eliminar nodo por ID
                if (archLoad) {
                    char letra;
                    std::cout << "Ingrese vertice a eliminar: ";
                    std::cin >> letra;
                    grafo.eliminar(letra);
                    grafo.imprimir();
                } else {
                    std::cout << "Primero cargue un archivo." << std::endl;
                }
                break;
            }
            case 5: {
                // Hallar ruta mínima entre dos vértices (Dijkstra)
                if (archLoad) {
                    char origen, destino;
                    std::cout << "Ingrese vertice origen: ";
                    std::cin >> origen;
                    std::cout << "Ingrese vertice destino: ";
                    std::cin >> destino;

                    int numRuta = grafo.rutaMinima(origen, destino);
                    std::cout << "Ruta mínima: " << numRuta << std::endl;
                } else {
                    std::cout << "Primero cargue un archivo." << std::endl;
                }
                break;
            }
            case 6: {
                std::cout << "Saliendo del programa." << std::endl;
                break;
            }
            default:
                break;
        }

        system("PAUSE");
    } while(resp != 6);
    std::ifstream archivo("arista.txt");
    return 0;
}

void menu(int &resp){
    do{
        system("cls");
        std::cout << "	------------ PROYECTO DE GRAFO -------------" << std::endl;
        std::cout << "	1. Cargar archivo" << std::endl;
        std::cout << "	2. Determinar si el grafo es fuertemente conexo" << std::endl;
        std::cout << "	3. Determinar si existen nodos fuente y nodos pozos" << std::endl;
        std::cout << "	4. Eliminar nodo por ID" << std::endl;
        std::cout << "	5. Hallar ruta minima entre dos vertices (Dijkstra)" << std::endl;
        std::cout << "	6. Salir del programa" << std::endl;
        std::cout << "	Respuesta: ";
        std::cin >> resp;
    } while(resp < 1 || resp > 6);
}

