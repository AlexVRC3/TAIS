
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
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
    Solucion(Grafo const& g) : visit(g.V(), false), maxim(0), contComp(0) {
        for (int v = 0; v < g.V(); ++v) {
            if (!visit[v]) { // se recorre una nueva componente conexa
                dfs(g, v);
                maxim = max(maxim, contComp);
                contComp = 0;
            }
        }
    }
    // tamaño máximo de una componente conexa
    int maximo() const {
        return maxim;
    }

private:
    vector<bool> visit; // visit[v] = se ha visitado el vértice v?
    int maxim; // tamaño de la componente mayor
    int contComp;
    void dfs(Grafo const& g, int v) {
        visit[v] = true;
        contComp++;
        for (int w : g.ady(v)) {
            if (!visit[w])
                 dfs(g, w);
        }
    }
};

void resuelveCaso() {

    int N, M;
    cin >> N >> M;
    Grafo g(N);
    int v, w;
    for (int i = 0; i < M; i++)
    {
        cin >> v >> w;
        g.ponArista(v - 1, w - 1);
    }

    Solucion sol(g);
    cout << sol.maximo() << "\n";
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
