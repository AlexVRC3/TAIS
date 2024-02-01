/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
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

	Dijkstra(DigrafoValorado<Valor> const& g, int orig) : dist(g.V(), 0), pq(g.V()), visit(g.V(), false), distDijkstra(g.V(), INF), distUsada(g.V(), 0) { // O(A log V) y esp adicional O(V)
		bfs(g, orig);
		distDijkstra[orig] = 0;
		pq.push(orig, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}
	bool hayCamino(int v) const { return visit[v]; }
	int  distanciaHasta(int v) { return distDijkstra[v]; }
	bool caminosMinimizados(int v) { return dist[v] == distUsada[v]; }

private:

	std::vector<Valor> distDijkstra;
	std::vector<int> dist;
	std::vector<bool> visit;
	std::vector<int> distUsada;
	IndexPQ<Valor> pq;

	void bfs(DigrafoValorado<int> const& g, int orig) {
		std::queue<int> q;
		dist[orig] = 0;
		visit[orig] = true;
		q.push(orig);

		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (auto w : g.ady(v)) {
				int other = w.hasta();
				if (!visit[other]) {
					dist[other] = dist[v] + 1;
					visit[other] = true;
					q.push(other);
				}
			}
		}
	}

	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (distDijkstra[w] > distDijkstra[v] + a.valor()) {
			distUsada[w] = distUsada[v] + 1;
			distDijkstra[w] = distDijkstra[v] + a.valor();
			pq.update(w, dist[w]);
			
		}
		else if (distDijkstra[w] == distDijkstra[v] + a.valor() && distUsada[w] > distUsada[v] + 1) {
			distUsada[w] = distUsada[v] + 1;
		}
	}

};

bool resuelveCaso() {
	using Camino = deque<AristaDirigida<int>>;
	// leer los datos de la entrada
	int N;

	cin >> N;

	if(!std::cin)
		return false;

	DigrafoValorado<int> dv(N);

	int C;
	cin >> C;
	int v, w, u;
	for (int i = 0; i < C; i++)
	{
		cin >> v >> w >> u;
		
		dv.ponArista({ v - 1, w - 1, u});
		dv.ponArista({ w - 1,v - 1, u });
	}


	int K;
	int origen, destino;
	cin >> K;
	for (int i = 0; i < K; i++)
	{
		cin >> origen >> destino;
		Dijkstra<int> dijkstra(dv,origen - 1);
		if (dijkstra.hayCamino(destino - 1)) {
			int distanciaMinima = dijkstra.distanciaHasta(destino);
			cout << dijkstra.distanciaHasta(destino - 1) << " " << (dijkstra.caminosMinimizados(destino - 1) ? "SI\n" : "NO\n");
		}
		else
			cout << "SIN CAMINO\n";
	}
	cout << "---\n";

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