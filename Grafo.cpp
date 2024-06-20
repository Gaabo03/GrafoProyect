#include "Grafo.h"

template <typename T>
Grafo<T>::Grafo() {}

template <typename T>
Grafo<T>::~Grafo() {
    matriz.clear();
    idsVertices.clear();
}
template <typename T>
int Grafo<T>::encontrarIndice(const T& ele) {
    for (size_t i = 0; i < idsVertices.size(); ++i) {
        if (idsVertices[i] == ele) {
            return i;
        }
    }
    return -1; // Retornar -1 si el elemento no se encuentra
}

template <typename T>
void Grafo<T>::crearMatriz(int numAristas, const std::vector<T>& idsOrigen, const std::vector<T>& idsDestino, const std::vector<int>& pesos) {
    if(idsOrigen.size() != numAristas || idsDestino.size() != numAristas || pesos.size() != numAristas) {
        std::cerr << "Error: los tama�os de los vectores no coinciden con el n�mero de aristas.\n";
        return;
    }

    for (int i = 0; i < numAristas; i++) {
        T idOrigen = idsOrigen[i];
        T idDestino = idsDestino[i];
        int peso = pesos[i];

        if (encontrarIndice(idOrigen) == -1) {
            idsVertices.push_back(idOrigen);
            for (int j = 0; j < matriz.size(); j++) {
                matriz[j].push_back(0);
            }
            matriz.push_back(std::vector<int>(idsVertices.size(), 0));
        }

        if (encontrarIndice(idDestino) == -1) {
            idsVertices.push_back(idDestino);
            for (int j = 0; j < matriz.size(); j++) {
                matriz[j].push_back(0);
            }
            matriz.push_back(std::vector<int>(idsVertices.size(), 0));
        }

        int indiceOrigen = encontrarIndice(idOrigen);
        int indiceDestino = encontrarIndice(idDestino);

        if (indiceOrigen < idsVertices.size() && indiceDestino < idsVertices.size()) {
            matriz[indiceOrigen][indiceDestino] = peso;
        } else {
            std::cerr << "Error: uno o ambos IDs de v�rtices no existen.\n";
        }
    }
}

template <typename T>
bool Grafo<T>::buscarVertice(const T &id) {
    return encontrarIndice(id) != -1;
}

template <typename T>
bool Grafo<T>::buscarArista(const T &idOrigen, const T &idDestino) {
    int indiceOrigen = encontrarIndice(idOrigen);
    int indiceDestino = encontrarIndice(idDestino);

    if (indiceOrigen == -1 || indiceDestino == -1) {
        return false; // uno o ambos v�rtices no existen
    }

    return matriz[indiceOrigen][indiceDestino] != 0; // existe una arista si el peso es diferente de 0
}

template <typename T>
void Grafo<T>::imprimir() {
    std::cout << "  ";
    for (int i = 0; i < idsVertices.size(); ++i) {
        std::cout << idsVertices[i] << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < idsVertices.size(); ++i) {
        std::cout << idsVertices[i] << " ";
        for (int j = 0; j < idsVertices.size(); ++j) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << "\n";
    }
}

template <typename T>
void Grafo<T>::eliminar(const T &ele) {
    int idx = encontrarIndice(ele);
    if (idx == -1) return;

    // Eliminar el vértice de la lista de IDs de vértices
    idsVertices.erase(idsVertices.begin() + idx);

    // Eliminar la fila y columna del vértice en la matriz de adyacencia
    matriz.erase(matriz.begin() + idx);
    for (int i = 0; i < matriz.size(); ++i) {
        matriz[i].erase(matriz[i].begin() + idx);
    }
}

template <typename T>
int Grafo<T>::rutaMinima(const T &ori, const T &des) {
    std::vector<Nodo<T> > distancias(idsVertices.size());
    for (size_t i = 0; i < idsVertices.size(); ++i) {
        distancias[i].id = idsVertices[i];
        distancias[i].distancia = (idsVertices[i] == ori) ? 0 : INT_MAX;
    }

    std::vector<bool> visitados(idsVertices.size(), false);

    for (size_t i = 0; i < idsVertices.size() - 1; ++i) {
        int minIndex = -1;
        for (size_t j = 0; j < idsVertices.size(); ++j) {
            if (!visitados[j] && (minIndex == -1 || distancias[j].distancia < distancias[minIndex].distancia)) {
                minIndex = j;
            }
        }

        visitados[minIndex] = true;

        for (size_t j = 0; j < idsVertices.size(); ++j) {
            int peso = matriz[minIndex][j];
            if (peso != 0 && distancias[minIndex].distancia != INT_MAX && distancias[minIndex].distancia + peso < distancias[j].distancia) {
                distancias[j].distancia = distancias[minIndex].distancia + peso;
            }
        }
    }

    for (size_t i = 0; i < idsVertices.size(); ++i) {
        if (distancias[i].id == des) {
            return distancias[i].distancia;
        }
    }

    return -1; // Retornar -1 si no se encuentra una ruta
}

template <typename T>
bool Grafo<T>::esFuertementeConexo() {
    // Aplicar el algoritmo de Warshall para obtener la matriz de cierre transitivo
    std::vector<std::vector<bool> > cierreTransitivo(idsVertices.size(), std::vector<bool>(idsVertices.size(), false));

    // Inicializar la matriz de cierre transitivo con las aristas existentes en el grafo
    for (int i = 0; i < idsVertices.size(); ++i) {
        for (int j = 0; j < idsVertices.size(); ++j) {
            if (matriz[i][j] != 0) {
                cierreTransitivo[i][j] = true;
            }
        }
    }

    // Calcular la matriz de cierre transitivo
    for (int k = 0; k < idsVertices.size(); ++k) {
        for (int i = 0; i < idsVertices.size(); ++i) {
            for (int j = 0; j < idsVertices.size(); ++j) {
                cierreTransitivo[i][j] = cierreTransitivo[i][j] || (cierreTransitivo[i][k] && cierreTransitivo[k][j]);
            }
        }
    }

    // Verificar si la matriz de cierre transitivo no contiene ceros arriba y abajo de la diagonal principal
    for (int i = 0; i < idsVertices.size(); ++i) {
        for (int j = 0; j < idsVertices.size(); ++j) {
            if (i != j && !cierreTransitivo[i][j]) {
                return false;
            }
        }
    }

    return true;
}

template <typename T>
void Grafo<T>::obtenerVerticesPozos() {
    std::vector<T> verticesPozos;

    for (int i = 0; i < idsVertices.size(); ++i) {
        bool esPozo = true;
        for (int j = 0; j < idsVertices.size(); ++j) {
            if (matriz[i][j] != 0) {
                esPozo = false;
                break;
            }
        }
        if (esPozo) {
            verticesPozos.push_back(idsVertices[i]);
        }
    }

    std::cout << "Vertices pozos: ";
    for (int i = 0; i < verticesPozos.size(); i++){
        std::cout << verticesPozos[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void Grafo<T>::obtenerVerticesFuentes() {
    std::vector<T> verticesFuentes;

    for (int i = 0; i < idsVertices.size(); ++i) {
        bool esFuente = true;
        for (int j = 0; j < idsVertices.size(); ++j) {
            if (matriz[j][i] != 0) {
                esFuente = false;
                break;
            }
        }
        if (esFuente) {
            verticesFuentes.push_back(idsVertices[i]);
        }
    }

    std::cout << "Vertices fuentes: ";
    for (int i = 0; i < verticesFuentes.size(); i++) {
        std::cout << verticesFuentes[i] << " ";
    }
    std::cout << std::endl;
}
