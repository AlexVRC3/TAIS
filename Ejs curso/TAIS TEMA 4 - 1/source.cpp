
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 * Gabriel Torres Martín TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
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
        Solucion(Grafo const& g) : visit(g.V(), false), ant(g.V()), contV(0), tieneCiclo(false){
            for (int v = 0; v < g.V(); v++)
            {
                if (!visit[v]) {
                    contV = dfs(g, v);
                }
            }
            if (esLibre(g)) {
                cout << "SI" << endl;
            }
            else cout << "NO" << endl;
        }

        bool esLibre(Grafo const& g) {
            return contV == g.V() && !tieneCiclo;
        }

    private:

        vector<bool> visit;
        vector<int> ant;
        int contV;
        bool tieneCiclo;

        int dfs(Grafo const& g, int v) {
            visit[v] = true;
            int tam = 1;
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    ant[w] = v;
                    tam += dfs(g, w);
                }
                else if (ant[v] != w) {
                    // Si visitamos un nodo ya visitado que no es el padre, hay un ciclo
                    tieneCiclo = true;
                }
            }
            return tam;
        }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int V, A;
    cin >> V;
    cin >> A;

    Grafo g(V);

    if (!std::cin)  // fin de la entrada
        return false;

    int v, w;
    for (int i = 0; i < A; i++)
    {
        cin >> v;
        cin >> w;
        g.ponArista(v, w);
    }

    // resolver el caso posiblemente llamando a otras funciones
    Solucion sol(g);

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
