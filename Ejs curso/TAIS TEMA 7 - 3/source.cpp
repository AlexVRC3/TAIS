/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
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
	using Camino = deque<AristaDirigida<Valor>>; // Corrige el tipo de Camino
public:

	Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig), dist(g.V(), INF), ulti(g.V()), pq(g.V()) { // O(A log V) y esp adicional O(V)
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}
	bool hayCamino(int v) const { return dist[v - 1] != INF; }
	int distanciaHasta(int v) const { return dist[v - 1]; }

	Valor distancia(int v) const { return dist[v]; }

	Camino camino(int v) const {
		Camino cam;
		// recuperamos el camino retrocediendo
		AristaDirigida<Valor> a;
		for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()]) {
			cam.push_front(a);
		}
		cam.push_front(a);
		return cam;
	}

private:

	std::vector<Valor> dist;
	std::vector<AristaDirigida<Valor>> ulti;
	IndexPQ<Valor> pq;
	int origen;

	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor();  ulti[w] = a;
			pq.update(w, dist[w]);
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
		if (dijkstra.hayCamino(destino)) {
			cout << dijkstra.distanciaHasta(destino) << ": ";
			Camino camino = dijkstra.camino(destino - 1);
			auto it = camino.begin();
			while (it != camino.end()) {
				cout << it->desde() + 1; // Imprime el punto de origen
				++it;

				if (it != camino.end()) {
					cout << " -> ";
				}
			}
			cout << " -> " << destino << "\n"; // Imprime el punto de destino
			
		}
		else
			cout << "NO LLEGA\n";
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