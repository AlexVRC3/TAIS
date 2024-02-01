
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 * Gabriel Torres Martín TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

#include "Grafo.h" // propios o los de las estructuras de datos de clase


/*@ <answer>

Coste O(V + A) v siendo eln numero de usuarios y A el numero de relaciones

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
class SocialNet {
    using Camino = std::stack<int>;

private:
    std::vector<bool> visitado;
    std::vector<int> amigos;
    Camino camino;

public:
    SocialNet(Grafo const& g) : visitado(g.V(), 0), amigos(g.V(), 0) {
        int sol;

        for (int v = 0; v < g.V(); v++) {
            if (!visitado[v]) {
                sol = dfs(g, v);
                camino.push(v);

                while (!camino.empty()) {
                    amigos[camino.top()] = sol;
                    camino.pop();
                }
            }
        }
    }

    int getFriends(int v) { return amigos[v]; }

private:
    int dfs(Grafo const& g, int v) {
        visitado[v] = true;
        int maxDepth = 1;

        for (int w : g.ady(v)) {
            if (!visitado[w]) {
                maxDepth += dfs(g, w);
                camino.push(w);
            }
        }

        return maxDepth;
    }
};


bool resuelveCaso() {
    int u, g; 
    cin >> u >> g;

    if (!std::cin) return false;

    Grafo grafo(u);

    for (int i = 0; i < g; i++) {
        int n; 
        cin >> n;

        if (n != 0) {
            int v, w; 
            cin >> v;

            for (int j = 0; j < n - 1; j++) {
                cin >> w;
                grafo.ponArista(v - 1, w - 1);
            }
        }
    }

    SocialNet socialNet(grafo);

    for (int i = 0; i < grafo.V(); i++)
        cout << socialNet.getFriends(i) << " ";
    cout << "\n";

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
