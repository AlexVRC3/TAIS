
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
// Escribe el c�digo completo de tu soluci�n aqu� debajo
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
