
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 * Gabriel Torres Martín TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"

/*@ <answer>

Coste O(V+A)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class ARM_Kruskal {

public:

    ARM_Kruskal(GrafoValorado<int> const& g) : coste(0), contVisitados(1), numVertices(g.V()) { // O(A log A) y espacio adicional O(A)
        PriorityQueue<Arista<int>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                contVisitados++;
                coste += a.valor();
                if (contVisitados == g.V())break;
            }
        }
    }
    int costeARM() const {
        return coste;
    } 

    bool esConexo() {
        return contVisitados == numVertices;
    }

private:
    vector<Arista<int>> _ARM;
    int coste;
    int contVisitados;
    int numVertices;
};



bool resuelveCaso() {

    // leer los datos de la entrada
    int I, P;

    cin >> I >> P;

    if (!std::cin)  // fin de la entrada
        return false;
    GrafoValorado<int> g(I);
    int v, w, valor;
    for (int i = 0; i < P; i++)
    {
        cin >> v >> w >> valor;
        g.ponArista({ v - 1,w - 1,valor });

    }

    ARM_Kruskal arm(g);
    if (arm.esConexo()) {
        cout << arm.costeARM() << endl;
    }
    else
        cout << "No hay puentes suficientes" << endl;
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
