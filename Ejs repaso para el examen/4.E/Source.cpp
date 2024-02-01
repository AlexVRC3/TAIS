
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#include "Grafo.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Solucion {
public:
    Solucion(Grafo const& g, int s) : visit(g.V(), false), dist(g.V()), s(s) {
        bfs(g);
    }
        
    vector<int> distancias() const {
        return dist;
    }
  
private:
    vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    vector<int> dist; // dist[v] = aristas en el camino s-v más corto
    int s;
        void bfs(Grafo const& g) {
        queue<int> q;
        dist[s] = 0; visit[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    dist[w] = dist[v] + 1; visit[w] = true;
                    q.push(w);
                }
            }
        }
    }
};


bool resuelveCaso() {

    // leer los datos de la entrada

    int N, C, alex, lucas, trabajo;
    cin >> N >> C >> alex >> lucas >> trabajo;
    if (!std::cin)  // fin de la entrada
        return false;

    Grafo g(N);
    int v, w;
    for (int i = 0; i < C; i++)
    {
        cin >> v >> w;
        g.ponArista(v - 1, w - 1);
    }
    alex -= 1;
    lucas -= 1;
    trabajo -= 1;

    Solucion solAlex(g,alex);
    Solucion solLucas(g,lucas);
    Solucion solTrabajo(g,trabajo);

    vector<int> distAlex = solAlex.distancias();
    vector<int> distLucas = solLucas.distancias();
    vector<int> distTrabajo = solTrabajo.distancias();

    int costeMin = distAlex[trabajo] + distLucas[trabajo];
    for (int i = 0; i < N; i++)
    {
        int coste = distAlex[i] + distLucas[i] + distTrabajo[i];
        if (coste < costeMin)
            costeMin = coste;
    }
    cout << costeMin << "\n";

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
