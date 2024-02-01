
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 * Gabriel Torres Martín TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Matriz.h"

/*@ <answer>
* 
NOTACIONES
----------
T = segundos que permite la botella estar bajo el agua
N = numero de cofres
Pi = profundidad a la que esta el cofre i
Oi = cantidad de oro que contiene el cofre i


RECURSION
---------

oro(i,j) = cantidad maxima de oro que se puede conseguir cuando quedan j segundos debajo del agua y podemos recoger cofres del 1 al i

                { oro(i - 1,j)                                      si 3Pi > j
oro(i,j) =      {
                { max(oro(i - 1, j) , oro(i - 1, j - 3Pi) + Oi      si 3Pi <= j

                     
Llamada inicial : oro(N,M)

EXPLICACION Y COSTE
-------------------

Se utiliza programación dinamica descendente de manera que se guarda en una matriz la solucion a los subproblemas que se van resolviendo, dado que en la recursion se repiten muchos calculos de
subproblemas. La solución queda almacenada en la posicion de la matriz N,T ya que la matriz tiene N + 1 filas y T + 1 columnas.

El coste en tiempo de resolver el problema esta en el orden de O(N * T) porque recorremos toda la matriz y sobre cada elemento realizamos operaciones constantes.
El coste en espacio esta en el orden de O(N * T) por la matriz donde almacenamos las soluciones de los problemas.

Podriamos conseguir reducir el espacio adicional a O(T) aplicando programacion ascendente pero al necesitar mostrar por pantalla el oro y la profundidad de cada cofre recogido es obligatorio
utilizar una matriz.

 @ </answer> */

struct Cofre {
    int profundidad;
    int oro;
};

int oro_rec(vector<Cofre> const& cofres, int i, int j, Matriz<int>& recogidos) {
    if (recogidos[i][j] != -1) // subproblema ya resuelto
        return recogidos[i][j];
    if (i == 0 || j == 0)
        recogidos[i][j] = 0;
    else if (cofres[i - 1].profundidad * 3 > j)
        recogidos[i][j] = oro_rec(cofres, i - 1, j, recogidos);
    else
        recogidos[i][j] = max(oro_rec(cofres, i - 1, j, recogidos), oro_rec(cofres, i - 1, j - cofres[i - 1].profundidad * 3, recogidos) + cofres[i - 1].oro);
    return recogidos[i][j];
}

int oro(const vector<Cofre>& cofres, int T, vector<bool>& sol, int& contCofres) {
    int n = cofres.size();
    Matriz<int> recogidos(n + 1, T + 1, -1);
    int valor = oro_rec(cofres, n, T, recogidos);

    int i = n, j = T;
    sol = vector<bool>(n, false);
    while (i > 0 && j > 0) {
        if (recogidos[i][j] != recogidos[i - 1][j]) { 
            sol[i - 1] = true;
            j = j - 3* cofres[i - 1].profundidad;
            contCofres++;
        }
        i--;
    }
    return valor;
}

bool resuelveCaso() {

    // leer los datos de la entrada

    int T, N;

    cin >> T;

    if (!std::cin)  // fin de la entrada
        return false;

    cin >> N;
    vector<Cofre> cofres(N);

    for (int i = 0; i < N; i++)
    {
        cin >> cofres[i].profundidad >> cofres[i].oro;
    }
    Matriz<int> pd(N, T);
    vector<bool> sol;
    int contCofres = 0;
    int maxOro = oro(cofres, T,sol, contCofres);

    cout << maxOro << endl;
    cout << contCofres << endl;
    for (int i = 0; i < sol.size(); i++)
    {
        if (sol[i])
            cout << cofres[i].profundidad << " " << cofres[i].oro << endl;
    }
    cout << "---" << endl;
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
