
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

int maximizarExitos(vector<int> const& e, vector<int> const& d) { // O(n) 
    int dIndex = 0;
    int nVictorias = 0;

    for (int i = 0; i < e.size(); i++) {
        if (e[i] <= d[dIndex]) {
            dIndex++;
            nVictorias++;
        }
    }

    return nVictorias;
}


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {

    int N;
    cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> enemigos(N);
    vector<int> defensa(N);
    for (int& i : enemigos)
        std::cin >> i;
    for (int& j : defensa)
        std::cin >> j;
    
    std::sort(enemigos.begin(), enemigos.end(), greater<int>());
    std::sort(defensa.begin(), defensa.end(), greater<int>());
    std::cout << maximizarExitos(enemigos,defensa) << "\n";

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
