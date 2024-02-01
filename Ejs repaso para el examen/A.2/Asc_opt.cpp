
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Matriz.h"
#include "EnterosInf.h"

/*@ <answer>

    dardos(i,j) = minimo numero de dardos para sumar la puntuacion j pudiendo caer en los sectores del 1 al i.

    CASOS BASE :
        - dardos(i,0) = 0
        - dardos(0,j) = Infinito

                  { dardos(i-1,j)                               si Si > j       Si: el sector en la posicion i del vector de sectores/puntuaciones
    dardos(i,j) = {
                  { min(dardos(i-1,j) , dardos(i, j - Si) + 1)  si Si <= j

    Llamada inicial dardos(N,P)

    Se utiliza programación dinamica ascendente y se recorre de arriba a abajo y de izquierda a derecha la matriz de N + 1 filas y P + 1 columnas (sectores y puntuaciones posibles respectivamente).
    Como para calcular el valor de la posicion (i,j) solo necesitamos el valor de las posiciones (i-1,j) y (i,j - Si) podemos reducir el espacio adicional a un vector en el cual tendremos los datos
    de la fila i - 1 a la izquierda y los datos de la fila i a la derecha. Para la reconstruccion de la solucion utilizamos un vector auxiliar en el que guardamos los valores de los sectores necesarios
    para sumar la puntuacion objetivo.

    -----------------
   | i  | j |  i -1 |
    -----------------
    El coste del algoritmo es del orden de O(N * P) ya que realizamos un recorrido completo de la matriz pero ahorramos en espacio adicional debido al uso de un vector en vez de una matriz y por ello
    el coste en espacio adicional es de O(P)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

EntInf resolver(const vector<int>& puntuaciones, const int P, vector<int>& sol) {
    int N = puntuaciones.size();
    vector<EntInf> dardos(P + 1, Infinito);
    dardos[0] = 0;
    for (int i = 1; i <= N; i++)
    {
        for (int j = puntuaciones[i - 1]; j <= P; j++)
        {
            dardos[j] = min(dardos[j], dardos[j - puntuaciones[i - 1]] + 1);
        }
    }

    if (dardos[P] != Infinito) {
        int i = N, j = P;
        while (j > 0) {
            if (puntuaciones[i - 1] <= j && dardos[j] == dardos[j - puntuaciones[i-1]] + 1) {
                sol.push_back(puntuaciones[i - 1]);
                j = j - puntuaciones[i - 1];
            }
            else
                i--;
        }
    }
    return dardos[P];
}


bool resuelveCaso() {

    // leer los datos de la entrada
    int objetivo, nSectores;
    cin >> objetivo >> nSectores;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> puntuaciones(nSectores);
    for (int i = 0; i < nSectores; i++)
    {
        cin >> puntuaciones[i];
    }
    vector<int> sol_sectores;
    EntInf sol = resolver(puntuaciones, objetivo, sol_sectores);
    if (sol == Infinito) {
        cout << "Imposible" << endl;
    }
    else {
        cout << sol << ": ";
        for (int i = 0; i < sol_sectores.size(); i++)
        {
            if (i != sol_sectores.size() - 1)
                cout << sol_sectores[i] << " ";
            else
                cout << sol_sectores[i];
        }
        cout << endl;
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
