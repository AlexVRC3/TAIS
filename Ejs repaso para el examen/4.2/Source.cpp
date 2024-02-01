
/*@ <authors>
 *
 * Alejandro Vida Ram�rez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Grafo.h"

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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
    // tama�o m�ximo de una componente conexa
    int maximo() const {
        return maxim;
    }

private:
    vector<bool> visit; // visit[v] = se ha visitado el v�rtice v?
    int maxim; // tama�o de la componente mayor
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
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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
