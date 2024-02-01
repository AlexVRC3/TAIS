
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
private:
    vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    int contVisit;
    vector<int> ant; 
    bool conexo;
    bool ciclo;
    void dfs(Grafo const& G, int v) {
        visit[v] = true;
        contVisit++;
        for (int w : G.ady(v)) {

            if (!visit[w]) {
                ant[w] = v;
                dfs(G, w);
            }
            else if (ant[v] != w)
                ciclo = true;
     
        }
   
    }

public:
    Solucion(Grafo const& g) : visit(g.V(), false), ant(g.V()), contVisit(0), ciclo(false), conexo(false) {
        for (int v = 0; v < g.V(); v++)
        {
            if (!visit[v])
                dfs(g, v);
            if (v == 0 && contVisit == g.V())
                conexo = true;
        }

    }
    // ¿hay camino del origen a v?
    bool hayCamino(int v) const {
        return visit[v];
    }

    bool esConexo() const {
        return conexo;
    }

    bool hayCiclo() const {
        return ciclo;
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int V, A;
    cin >> V;
    if (!std::cin)  // fin de la entrada
        return false;

    cin >> A;
    Grafo g(V);
    int v, w;
    for (int i = 0; i < A; i++)
    {
        cin >> v >> w;
        g.ponArista(v , w );
    }

    Solucion sol(g);

    if (!sol.hayCiclo() && sol.esConexo())
        cout << "SI\n";
    else
        cout << "NO\n";

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
