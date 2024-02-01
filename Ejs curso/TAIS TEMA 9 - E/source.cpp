/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

#include "DigrafoValorado.h"
#include "IndexPQ.h"

/*@ <answer>

Enfoque de la Solución:

La solución implementa un enfoque voraz para asignar pueblos a las plantas de manera eficiente. Primero, calculamos las distancias mínimas desde las plantas a todos los pueblos utilizando el algoritmo de Dijkstra. 
Luego, ordenamos los pueblos en función de la distancia más corta entre las dos plantas.La asignación de pueblos se realiza siguiendo un enfoque voraz. Seleccionamos los pueblos en orden ascendente según la distancia más corta entre las plantas. 
Cada pueblo se asigna a la planta que ofrezca la distancia más corta. Mantenemos un equilibrio, asegurándonos de que cada planta suministre a la mitad de los pueblos ((N - 2)/ 2). Esta estrategia minimiza el coste total de transporte, ya que elegimos los pueblos más cercanos a cada planta en cada paso.
Además, garantizamos que se cumplan las restricciones de suministro equitativo entre las dos plantas.

Supongamos que una solucion voraz V asigna los pueblos de manera voraz y O es una asignación óptima que minimiza el coste total. Definimos D como la diferencia de coste total entre las soluciones O y V (es decir, D = Coste (O) -  Coste(V))

Ahora, queremos demostrar que la diferencia D es igual a cero, es decir, que la solución voraz es óptima. La solución voraz asigna cada pueblo a la planta que ofrece el menor coste, manteniendo un equilibrio en la asignación. Si O también asigna pueblos manteniendo un equilibrio, entonces la diferencia en el número de pueblos asignados por cada planta debe ser cero.
La solución voraz ordena los pueblos según la distancia más corta a alguna de las plantas y luego asigna pueblos en orden ascendente. Si O asigna pueblos de una manera que no sigue este orden, podría haber oportunidades de mejorar la asignación y reducir el coste total por lo que O no seria optima.

Coste de la Solución:

El coste de la solución se desglosa de la siguiente manera:

1. Algoritmo de Dijkstra: El coste es del orden de O(A log V) donde A es el numero de aristas(carreteras) y V es el numero de vertices(pueblos + plantas)
2. Ordenamiento de pueblos: El ordenamiento de los pueblos tiene coste O(V log V) donde V es el número de pueblos.
3. Iteración sobre pueblos para asignar y calcular el coste: Iterar sobre los pueblos y calcular el coste es del orden de O(V)
4. Operaciones como las de IndexPQ que no influyen en el coste total ya que son mas pequeñas que las mencionadas arriba.

En resumen, el coste del algoritmo será O(A log V) debido al algoritmo de dijkstra ya que además en estos grafos O(A log V) es mas grande que O(V log V) suponiendo problemas de grafos densos.
Y en cuanto a espacio adicional O(V)


 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>



//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

using lli = long long int;

template <typename Valor>
class Dijkstra {
public:
    Dijkstra(const DigrafoValorado<Valor>& grafo, int origen) : dist(grafo.V(), numeric_limits<Valor>::max()), pq(grafo.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : grafo.ady(v))
                relajar(a);
        }
    }

    vector<lli> costes() const {
        return dist;
    }


private:
    vector<lli> dist;
    IndexPQ<Valor> pq;

    void relajar(const AristaDirigida<Valor>& a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }
};


vector<vector<lli>> calcularCostes(const DigrafoValorado<int>& grafo, int N) { // O(A log V)

    Dijkstra<int> dijkstraNorte(grafo, 0);
    vector<lli> costesDesdeNorte = dijkstraNorte.costes();

    Dijkstra<int> dijkstraSur(grafo, N - 1);
    vector<lli> costesDesdeSur = dijkstraSur.costes();

    return {costesDesdeNorte, costesDesdeSur };
}

struct Pueblo {
    lli costeNorte;
    lli costeSur;
    int indice;   
};

bool compararPueblos(const Pueblo& uno, const Pueblo& otro) {
    // Priorizar pueblos con costes diferentes
    if (uno.costeNorte != uno.costeSur && otro.costeNorte != otro.costeSur) {
        return min(uno.costeNorte, uno.costeSur) < min(otro.costeNorte, otro.costeSur);
    }
    if (uno.costeNorte == uno.costeSur && otro.costeNorte != otro.costeSur) {
        return false; // Poner pueblos con costes iguales al final
    }
    if (uno.costeNorte != uno.costeSur && otro.costeNorte == otro.costeSur) {
        return true; // Poner pueblos con costes iguales al final
    }
    // Si ambos tienen costes iguales, usar el Ã­ndice para desempatar
    return uno.indice < otro.indice;
}

lli asignarPueblosYCalcularCoste(const vector<lli>& distNorte, const vector<lli>& distSur, int V) {
    int pueblosPorPlanta = (V - 2) / 2;
    vector<Pueblo> pueblosOrdenados;
    for (int i = 1; i < V - 1; ++i) {
        pueblosOrdenados.push_back({ distNorte[i], distSur[i], i });
    }

    sort(pueblosOrdenados.begin(), pueblosOrdenados.end(), compararPueblos);

    lli costeTotal = 0;
    int pueblosAsignadosNorte = 0;
    int pueblosAsignadosSur = 0;

    // Primero procesar pueblos con costes diferentes
    for (const auto& pueblo : pueblosOrdenados) {
        if (pueblo.costeNorte != pueblo.costeSur) {
            if (pueblosAsignadosNorte < pueblosPorPlanta && (pueblo.costeNorte < pueblo.costeSur || pueblosAsignadosSur == pueblosPorPlanta)) {
                costeTotal += pueblo.costeNorte;
                pueblosAsignadosNorte++;
            }
            else {
                costeTotal += pueblo.costeSur;
                pueblosAsignadosSur++;
            }
        }
    }

    // Luego asignar pueblos con costes iguales
    for (const auto& pueblo : pueblosOrdenados) {
        if (pueblo.costeNorte == pueblo.costeSur) {
            if (pueblosAsignadosNorte < pueblosPorPlanta) {
                costeTotal += pueblo.costeNorte;
                pueblosAsignadosNorte++;
            }
            else {
                costeTotal += pueblo.costeSur;
                pueblosAsignadosSur++;
            }
        }
    }

    return costeTotal * 2; // Multiplicar por 2 para incluir el viaje de vuelta
}

bool resuelveCaso() {
    int N, M;
    cin >> N >> M;
    if (!cin) return false;

    DigrafoValorado<int> grafo(N);
    for (int i = 0; i < M; ++i) {
        int v, w, valor;
        cin >> v >> w >> valor;
        grafo.ponArista({ v - 1, w - 1, valor });
        grafo.ponArista({ w - 1, v - 1, valor });
    }

    auto costes = calcularCostes(grafo, N);
    lli costeTotal = asignarPueblosYCalcularCoste(costes[0], costes[1], N);

    cout << costeTotal << endl;

    return true;
}
int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}