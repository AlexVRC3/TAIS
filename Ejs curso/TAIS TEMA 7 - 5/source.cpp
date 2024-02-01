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

#include "DigrafoValorado.h"  // Incluye tus propias implementaciones
#include "IndexPQ.h"

/*@ <answer>

 Para resolver el problema creamos el Digrafo Valorado con un vertice de mas que va a ser el "vertice ficticio" lo cual nos va a permitir no tener que hacer una llamada al algoritmo
 Dijkstra B veces ya que podemos conectar todos los borriquines a este vertice y de esta manera con tener calculadas las distancias minimas desde todos los vertices al vertice ficticio
 tenemos lo necesario para contestar al problema. El coste seria del orden de O(C log P) y con un espacio adicional en O(P). Los costes de las operaciones estan especificados al lado
 de las llamadas en el codigo.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Solucion {
#define INF 2147483647 // max(int)

public:

	Solucion(DigrafoValorado<int> const& g, int distance) : pq(g.V()), dist(g.V(), INF), borriquin(g.V(), false), numPueblos(0), D(distance), contados(g.V(), false){ // O(A log V) y esp adicional O(V)
		
	}

	void dijkstra(DigrafoValorado<int> const& g, int orig) {
		dist[orig] = 0;
		pq.push(orig, 0); // O(log P)

		while (!pq.empty()) {
			int v = pq.top().elem;
			pq.pop(); // O(log P)

			if (esBorriquin(v) && !contados[v]) {
				numPueblos++; 
				contados[v] = true;
			}
				
			for (auto a : g.ady(v)) // Se pueden relajar C aristas en total asi que estaria acotado en O(C)
				relajar(a);

		}
	}
	int getNumPueblos() const {
		return numPueblos;
	}

	void marcarBorriquin(int pueblo) {
		borriquin[pueblo] = true;
	}

	bool esBorriquin(int v) {
		return borriquin[v];
	}


private:

	vector<int> dist;
	IndexPQ<int> pq; // O(log P)
	vector<bool> borriquin;
	vector<bool> contados;
	int numPueblos;
	int D;

	void relajar(AristaDirigida<int> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor();
			if (dist[w] <= D && !contados[w]) {
				contados[w] = true;
				numPueblos++;
			}
			pq.update(w, dist[w]); // O(log P)

		}
	}
};


bool resuelveCaso() {
    int D, P, C;

    cin >> D >> P >> C;

    if (!std::cin)
        return false;

    DigrafoValorado<int> grafo(P + 1); // Vertice ficticio P

    int v, w, u;
    for (int i = 0; i < C; i++) {
        cin >> v >> w >> u;
        grafo.ponArista({ v - 1, w - 1, u });
        grafo.ponArista({ w - 1, v - 1, u });
    }

	Solucion sol(grafo, D);
	
    int B;
    cin >> B;
	std::vector<int> borriquines(B);
	for (int i = 0; i < B; i++) {
		cin >> borriquines[i];
		borriquines[i]--;
		sol.marcarBorriquin(borriquines[i]);
		grafo.ponArista({ P, borriquines[i], 0 }); // Introducimos aristas de valor 0 que conectan el vertice ficticio con los borriquines
	}
	
	sol.dijkstra(grafo, P);
	

	cout << sol.getNumPueblos() << endl;

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

