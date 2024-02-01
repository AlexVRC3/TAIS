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

	Dijkstra(DigrafoValorado<Valor> const& g) : dist(g.V(), INF), pq(g.V()) { // O(A log V) y esp adicional O(V)
		dist[0] = 0;
		pq.push(0, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}
	bool hayCamino(int v) const { return dist[v - 1] != INF; }
	int distanciaHasta(int v) const { return dist[v - 1]; }


private:

	std::vector<Valor> dist;
	IndexPQ<Valor> pq;

	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor(); 
			pq.update(w, dist[w]);
		}
	}
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int N;

	cin >> N;

	if(N == 0)
		return false;

	std::vector<int> tiemposCarga(N);
	for (int& i : tiemposCarga)
		cin >> i;

	DigrafoValorado<int> dv(N);

	int M;
	cin >> M;
	int v, w, k;
	for (int i = 0; i < M; i++)
	{
		cin >> v >> w >> k;
		k += tiemposCarga[w - 1];
		if (v == 1) k += tiemposCarga[0];

		dv.ponArista({ v - 1, w - 1, k });
	}

	Dijkstra<int> dijkstra(dv);

	if (dijkstra.hayCamino(N))
		cout << dijkstra.distanciaHasta(N) << "\n";
	else
		cout << "IMPOSIBLE\n";

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