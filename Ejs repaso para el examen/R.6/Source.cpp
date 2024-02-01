
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "DigrafoValorado.h"
#include "IndexPQ.h"

/*@ <answer>

Realizamos un Dijkstra con el grafo invertido para calcular las distancias desde la salida al resto de vertices para saber cuantos ratones pueden escapar del laberinto.
Una vez hemos calculado las distancias(tiempo que tardan) si ese tiempo es menor que T significa que podrán salir. El coste del algoritmo es del orden de O(A log V) siendo 
A el numero de aristas del grafo y V el numero de vertices. Por otro lado invertir el grafo tiene coste O(N + P) siendo N el numero de celdas y P el numero de pasadizos.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
class Dijkstra {
public:
    Dijkstra(DigrafoValorado<int> const& g, int orig) : origen(orig), dist(g.V(), INF), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
 
    int distancia(int v) const { return dist[v]; }
    
private:
    const int INF = std::numeric_limits<int>::max();
    int origen;
    vector<int> dist;
    IndexPQ<int> pq;
    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }
};

bool resuelveCaso() {

    int N, S, T, P;
    cin >> N >> S >> T >> P;

    if (!std::cin)  // fin de la entrada
        return false;
    DigrafoValorado<int> dg(N);
    int v, w, val;
    for (int i = 0; i < P; i++)
    {
        cin >> v >> w >> val;
        dg.ponArista({ v - 1,w - 1,val });
    }
    int ratones = 0;
    Dijkstra sol(dg.inverso(), S - 1);
    for (int i = 0; i < N; i++)
    {
        if (sol.distancia(i) <= T)
            ratones++;
    }
   
    cout << ratones - 1 << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

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
