
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"

/*@ <answer>

La solucion consiste en aplicar el algoritmo de Kruskal para encontrar el arbol de recubrimiento minimo. Como nos piden el numero minimo de horas que tendremos que esperar
para que todas los pueblos vuelvan a estar conectados entre sí, lo que nos estan pidiendo realmente es la arista con mayor peso del ARM que mientras sea conexo, siempre sera 
la ultima arista añadida al vector en el que almacenamos la solución. Puede confundirse con obtener el coste pero es sencillo darse cuenta de que si por ejemplo en el primer caso
cogemos el coste que sería 30 estamos sumando las 10 horas de la primera carretera a las 20 de la segunda cuando en realidad una vez hayan pasado 20 horas ambas carreteras estarán
transitables. Por último el coste de la solucion es del orden de O(A log A) siendo V el numero de vertices y A el numero de aristas.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename Valor>
class ARM_Kruskal {
private:
    bool conexo;
    int max;
public:

    bool esConexo() const {
        return conexo;
    }
    int getAristaMax() const {
        return max;
    }
    ARM_Kruskal(GrafoValorado<Valor> const& g) : conexo(true), max(0) {
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                if (cjtos.num_cjtos() == 1) {
                    max = a.valor();
                    break;
                }
            }
        }
        if (cjtos.num_cjtos() > 1)
            conexo = false;
    }
};

void resuelveCaso() {

    int N, M;
    cin >> N >> M;
    GrafoValorado<int> g(N);
    int u, w, val;
    for (int i = 0; i < M; i++)
    {
        cin >> u >> w >> val;
        g.ponArista({ u - 1,w - 1,val });
    }
    ARM_Kruskal<int> sol(g);
    if (sol.esConexo())
        cout << sol.getAristaMax() << endl;
    else
        cout << "Imposible\n";
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
