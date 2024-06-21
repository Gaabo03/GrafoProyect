#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>

template <typename T>
struct Nodo {
    T id;
    int distancia;
};

template <typename T>
class Grafo {
private:
    std::vector<std::vector<int> > matriz; //Matriz de adyacencia
    std::vector<T> idsVertices;

public:
    Grafo(); //Constructor
    ~Grafo(); //Destructor

	int encontrarIndice(const T& ele); // Encuentra el indice de un elemento en el vector de idsVertices
    void crearMatriz(int numAristas, const std::vector<T>& idsOrigen, const std::vector<T>& idsDestino, const std::vector<int>& pesos); // Llena la matriz de adyacencia con entrada del usuario
    bool buscar(const T &ele); // Busca un elemento en la matriz de adyacencia
    void imprimir(); // Imprime el recorrido en profundidad y en anchura
    void eliminar(const T &ele); // Elimina un nodo del grafo
    bool buscarVertice(const T &id); // Busca un vertice en el grafo
    bool buscarArista(const T &idOrigen, const T &idDestino); // Busca una arista en el grafo
    int rutaMinima(const T &ori, const T &des); // Encuentra la ruta minima entre dos vertices
    bool esFuertementeConexo(); // Verifica si el grafo es fuertemente conexo
    void obtenerVerticesPozos(); // Obtiene los vertices pozo
    void obtenerVerticesFuentes(); // Obtiene los vertices fuente
};

#endif
