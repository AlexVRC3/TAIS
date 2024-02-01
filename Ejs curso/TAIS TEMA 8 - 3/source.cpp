
/*@ <authors>
 *
 * Alejandro Vida Ram�rez de Arellano TAIS71
 * Gabriel Torres Mart�n TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;



/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */

int minimizarEquipaciones(vector<int> const& t, vector<int> & e) { // O(n) 
    int i = 0, j = 0;
    int equipacionesAdicionales = t.size();

    while (i < t.size() && j < e.size()) {
        if (t[i] == e[j] || t[i] + 1 == e[j]) { // La prenda le vale
            i++; j++; equipacionesAdicionales--;
        }
        else if (t[i] > e[j]) // El jugador m�s peque�o es mayor que la minima talla
            j++;
        else
            i++;
    }

    return equipacionesAdicionales;
}


// ================================================================
// Escribe el c�digo completo de tu soluci�n aqu� debajo
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
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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
