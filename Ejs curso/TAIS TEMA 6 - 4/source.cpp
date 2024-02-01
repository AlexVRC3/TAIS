
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
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class ARM_Kruskal {

public:

    ARM_Kruskal(GrafoValorado<int> const& g, int A) : coste(0), contVisitados(1), numVertices(g.V()), _numAeropuertos(0) { // O(A log A) y espacio adicional O(A)
        PriorityQueue<Arista<int>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);

            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                contVisitados++;
                coste += a.valor();
                if (contVisitados == g.V()) 
                    break;
            }
        }
        _numAeropuertos = cjtos.num_cjtos();
        coste += _numAeropuertos * A;
       
    }
    int costeARM() const {
        return coste;
    }

    int numAeropuertos() const{
        return _numAeropuertos;
    }

private:
    int coste;
    int contVisitados;
    int numVertices;
    int _numAeropuertos;
};

bool resuelveCaso() {

    // leer los datos de la entrada

    int N, M, A;
    cin >> N >> M >> A;

    if (!std::cin)  // fin de la entrada
        return false;
    int x, y, c;
    GrafoValorado<int> g(N);
    for (int i = 0; i < M; i++)
    {
        cin >> x >> y >> c;
        if(c < A) // Solo si pone la arista si es mejor un camino que un aeropuerto
            g.ponArista({ x - 1,y - 1,c });

    }
    ARM_Kruskal arm(g, A);
    
    cout << arm.costeARM() << " " << arm.numAeropuertos() << endl;
    


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
