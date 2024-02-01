/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;


/*@ <answer>

 El coste del algoritmo es O(N log N) ya que tenemos un for que se ejecuta N veces y luego utilizamos push y pop dentro del for que tiene coste log N

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Cliente{
    int prio;
    int caja;
};

bool operator<(Cliente const& a, Cliente const& b) {
	return a.prio == b.prio ? a.caja > b.caja : a.prio > b.prio;

}

bool resuelveCaso() {

    // leer los datos de la entrada
    int C, N;

    cin >> N; cin >> C;
    if (C == 0 && N == 0)
        return false;

	priority_queue<Cliente> pq;
	int c;

	if (N > C) {
		cout << C + 1 << endl;

		for (int i = 0; i < C; i++) {
			cin >> c;
		}
	}
	else {

		for (int i = 1; i <= N; i++) {
			cin >> c;
			pq.push({ c, i });
			C--;
		}

		while (C > 0) {
			Cliente e = pq.top();
			pq.pop();
			cin >> c;
			pq.push({ c + e.prio, e.caja });
			C--;
		}

		Cliente e = pq.top();
		cout << e.caja << endl;
	}
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
