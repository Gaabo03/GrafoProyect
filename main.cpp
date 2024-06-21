#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "Grafo.cpp"

/*
Proyecto de grafos - 2024-1 - Estructura de datos
Gabriel Enrique Ulacio Rangel V-30443148
Gustavo Enrique Morillo Vetancourt V-30981606
*/

void menu(int &);
void cargarArchivo(Grafo<char>&, bool&);
void esFuertementeConexo(Grafo<char>, bool);
void eliminarVertice(Grafo<char>&, bool);
void rutaMinimaDijkstra(Grafo<char>, bool);

// Funcion principal
int main() {
	Grafo<char> grafo;
	
	int resp;
    bool archLoad=false; // Variable para verificar si se ha cargado el archivo

    // Bucle principal del programa
	do {
        menu(resp); // Muestra el menu y obtiene la respuesta del usuario
        switch(resp) {
            case 1: // Carga el archivo arista.txt
            	cargarArchivo(grafo, archLoad);
            	break;
            case 2: // Determinar si el grafo es fuertemente conexo
                esFuertementeConexo(grafo, archLoad);
                break;
            case 3: // Eliminar nodo por ID
            	eliminarVertice(grafo, archLoad);
                break;
            case 4: // Hallar ruta minima entre dos vetices (Dijkstra)
            	rutaMinimaDijkstra(grafo, archLoad);
            	break;
            case 5: 
                std::cout << "\n\tSaliendo del programa." << std::endl;
                break;
            default:
                break;
        }
		std::cout << "\n\t";
        system("PAUSE");
    } while(resp != 5);
    return 0;
}

// Muestra el menu y obtiene la respuesta del usuario
void menu(int &resp){
    do{
        system("cls");
        std::cout << "	---------------- PROYECTO DE GRAFO ----------------" << std::endl;
        std::cout << "	1. Cargar archivo" << std::endl;
        std::cout << "	2. Determinar si el grafo es fuertemente conexo (muestra nodos fuente y pozo)" << std::endl;
        std::cout << "	3. Eliminar nodo por ID" << std::endl;
        std::cout << "	4. Hallar ruta minima entre dos vertices (Dijkstra)" << std::endl;
        std::cout << "	5. Salir del programa" << std::endl;
        std::cout << "	Respuesta: ";
        std::cin >> resp;
    } while(resp < 1 || resp > 5);
}

// Carga el archivo arista.txt
void cargarArchivo(Grafo<char>& grafo, bool &archLoad){
    std::ifstream archivo("arista.txt");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo arista.txt" << std::endl;
        archLoad = false;
        return;
    }
    
    int numVertices;
    std::vector<char> vOrigen, vDestino;
    std::vector<int> vPeso;
    std::string linea;
    
    archivo >> numVertices;
    
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
    
    if(vOrigen.size() != numVertices || vDestino.size() != numVertices || vPeso.size() != numVertices) {
        std::cerr << "\n\tError: los tamanos de los vectores no coinciden con el numero de aristas.\n\n\t";
        archLoad = false;
        return;
    }
    grafo.crearMatriz(numVertices, vOrigen, vDestino, vPeso);
    std::cout << "\n\tSe ha creado el grafo correctamente:" << std::endl;
    grafo.imprimir();
    archLoad = true;
}

// Determinar si el grafo es fuertemente conexo
void esFuertementeConexo(Grafo<char> grafo, bool archLoad){
	if (archLoad) {
        bool esConexo = grafo.esFuertementeConexo();
        std::cout << "\n\tEs fuertemente conexo?: " << (esConexo ? "Si" : "No") << std::endl << "\n";
        
        if (!esConexo){
        	
        	grafo.obtenerVerticesFuentes();
            grafo.obtenerVerticesPozos();
		}
    } else {
        std::cout << "\n\tPrimero cargue un archivo." << std::endl << "\t";
    }
}

// Eliminar nodo por ID
void eliminarVertice(Grafo<char>& grafo, bool archLoad){
	if (archLoad) {
        char letra;
        std::cout << "\n\tIngrese vertice a eliminar: ";
        std::cin >> letra;
        grafo.eliminar(letra);
        grafo.imprimir();
    } else {
        std::cout << "\n\tPrimero cargue un archivo." << std::endl << "\t";
    }
}

// Hallar ruta minima entre dos vertices (Dijkstra)
void rutaMinimaDijkstra(Grafo<char> grafo, bool archLoad){
	if (archLoad) {
	    char origen, destino;
	    std::cout << "\n\tIngrese vertice origen: ";
	    std::cin >> origen;
	    std::cout << "\tIngrese vertice destino: ";
	    std::cin >> destino;
	    int numRuta = grafo.rutaMinima(origen, destino);
	    if (numRuta == -1){
	    	std::cout << "\tNo existe camino posible."<< std::endl;
		} else {
			std::cout << "\tRuta minima: " << numRuta << std::endl;
		}
	} else {
	    std::cout << "\n\tPrimero cargue un archivo." << std::endl;
	}
}
