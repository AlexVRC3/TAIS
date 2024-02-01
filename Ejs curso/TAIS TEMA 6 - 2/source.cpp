
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 * Gabriel Torres Martín TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;

#include "GrafoValorado.h"

/*@ <answer>

Coste O(V+A)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Solucion {
    

public:
    Solucion(GrafoValorado<int>const &g, int ini, int dest, int anchura):visit(g.V(), false), ini(ini), dest(dest) {
        dfs(g, ini, anchura);
    }

    bool answer() {
        return visit[dest];
    }


private:

    vector<bool> visit;
    int ini;
    int dest;

    void dfs(GrafoValorado<int> const& g, int v, int anchura) {
        visit[v] = true;
        for (auto a : g.ady(v)) {
            if (anchura <= a.valor()) {
                int w = a.otro(v);
                if (!visit[w])
                    dfs(g, w, anchura);
            }
        }
    }
};



bool resuelveCaso() {

    // leer los datos de la entrada
    int V, E, K;

    cin >> V >> E;

    if (!std::cin)  // fin de la entrada
        return false;
    GrafoValorado<int> g(V);
    int v, w, valor;
    for (int i = 0; i < E; i++)
    {
        cin >> v >> w >> valor;
        g.ponArista({ v - 1,w - 1,valor });
        
    }
    cin >> K;
    int ini, fin, anchura;
    for (int i = 0; i < K; i++)
    {
        cin >> ini >> fin >> anchura;
        Solucion sol(g, ini - 1, fin - 1, anchura);

        if (sol.answer()) {
            cout << "SI" << endl;
        }
        else
            cout << "NO" << endl;
    }

    // resolver el caso posiblemente llamando a otras funciones

    // escribir la solución

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
