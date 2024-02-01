
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
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

Modificamos el relajar de Dijkstra para calcular en vez de los caminos minimos sumando los pesos de las aristas, que considere que como puede respirar entre camaras, el valor del camino mas con
veniente es el valor maximo de las aristas encontradas en el camino hasta ese punto. Es decir la comparacion tiene que ser contra el peso de la arista actual y no con la suma de distancias.
Coste O(A log V) debido a que se pueden relajar A aristas y hacemos operaciones de pop y update en la cola de prioridad de vertices y en espacio adicional O(V) por instanciar la cola de 
prioridad y los vectores.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename Valor>
class Dijkstra {
public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig), dist(g.V(), INF), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
   
    bool hayCamino(int v) const { 
        return dist[v] != INF;
    }

    int distancia(int v) {
        return dist[v];
    }
private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    vector<Valor> dist;
    IndexPQ<Valor> pq;
  
    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        Valor aristaMax = max(dist[v], a.valor());
        if (dist[w] > aristaMax) {
            dist[w] = aristaMax;
            pq.update(w, dist[w]);
        }
    }

};

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, M;
    cin >> N >> M;

    if (!std::cin)  // fin de la entrada
        return false;
    DigrafoValorado<int> g(N);
    int v, w, val;
    for (int i = 0; i < M; i++)
    {
        cin >> v >> w >> val;
        g.ponArista({ v - 1 , w - 1, val });
        g.ponArista({ w - 1, v - 1, val });
    }
    int PJ, CT;
    cin >> PJ >> CT;
    PJ--;
    CT--;
    Dijkstra<int> sol(g, PJ);
   
    if (!sol.hayCamino(CT))
        cout << "IMPOSIBLE\n";
    else {
        cout << sol.distancia(CT) << "\n";
    }
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
