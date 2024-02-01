
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 * Gabriel Torres Martín TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;



/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

int minimizarEquipaciones(vector<int> const& t, vector<int> & e) { // O(n) 
    int i = 0, j = 0;
    int equipacionesAdicionales = t.size();

    while (i < t.size() && j < e.size()) {
        if (t[i] == e[j] || t[i] + 1 == e[j]) { // La prenda le vale
            i++; j++; equipacionesAdicionales--;
        }
        else if (t[i] > e[j]) // El jugador más pequeño es mayor que la minima talla
            j++;
        else
            i++;
    }

    return equipacionesAdicionales;
}


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {

    int N, M;
    cin >> N >> M;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> tallasJugadores(N);
    vector<int> equipacionesDisponibles(M);
    for (int& i : tallasJugadores)
        std::cin >> i;
    for (int& j : equipacionesDisponibles)
        std::cin >> j;

    std::sort(tallasJugadores.begin(), tallasJugadores.end(), less<int>());
    std::sort(equipacionesDisponibles.begin(), equipacionesDisponibles.end(), less<int>());

    std::cout << minimizarEquipaciones(tallasJugadores, equipacionesDisponibles) << "\n";

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
