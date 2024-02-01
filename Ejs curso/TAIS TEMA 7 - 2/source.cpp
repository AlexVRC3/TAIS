/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


template <typename Valor>
class Dijkstra {

#define INF 2147483647 // max(int)
public:

	Dijkstra(DigrafoValorado<Valor> const& g) : dist(g.V(), INF), pq(g.V()), caminos(g.V(), 0) { // O(A log V) y esp adicional O(V)
		dist[0] = 0;
		caminos[0] = 1; // Camino vacío
		pq.push(0, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}
	bool hayCamino(int v) const { return dist[v - 1] != INF; }
	int distanciaHasta(int v) const { return dist[v - 1]; }
	int diferentesCaminos(int v) const { return caminos[v - 1]; }


private:

	std::vector<Valor> dist;
	std::vector<int> caminos;
	IndexPQ<Valor> pq;
	
	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor();
			caminos[w] = caminos[v]; // Nueva forma de llegar a w
			pq.update(w, dist[w]);
		}
		else if (dist[w] == dist[v] + a.valor()) {
			caminos[w] += caminos[v]; // Si la distancia es la misma hemos encontrado otra forma de llegar a w pero ahora las formas de llegar son las que ya tenia mas las de llegar al vertice desde el que hemos detectado el nuevo camino
		}
	}
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int N;

	cin >> N;

	if(!std::cin)
		return false;

	DigrafoValorado<int> dv(N);

	int M;
	cin >> M;
	int v, w, k;
	for (int i = 0; i < M; i++)
	{
		cin >> v >> w >> k;
		dv.ponArista({ v - 1, w - 1, k });
		dv.ponArista({ w - 1, v - 1, k });
	}

	Dijkstra<int> dijkstra(dv);

	cout << (dijkstra.hayCamino(dv.V()) ? dijkstra.diferentesCaminos(N) : 0) << "\n";

	return true;
}

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