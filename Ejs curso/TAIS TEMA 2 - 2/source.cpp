/*@ <answer>
 *
 * Nombre y Apellidos: Alejandro Vida
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

struct person {
    int id;
    int period;
    int timestamp;
};

bool operator<(person const& a, person const& b) {
    return b.timestamp < a.timestamp ||
        (a.timestamp == b.timestamp && b.id < a.id);
}

bool resuelveCaso() {
    int n;

    std::cin >> n;

    if (n == 0) return false;

    priority_queue<person> peopleList;
    for (int i = 0; i < n; ++i) {
        int id, period;
        std::cin >> id >> period;

        peopleList.push({ id, period, period });
    }

    int k; std::cin >> k;
    for (int i = 0; i < k; ++i) {
        person temp = peopleList.top();
        peopleList.pop();

        std::cout << temp.id << "\n";

        temp.timestamp += temp.period;

        peopleList.push(temp);
    }

    std::cout << "---\n";

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