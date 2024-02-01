
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#include "Matriz.h"

/*@ <answer>

cazatesoros(i,j) = maxima cantidad de oro que se puede obtener si se tienen j segundos de aire para bucear y se pueden coger los cofres del 1 al i.

                   { cazatesoros(i-1, j)                                                                si 3 * Ci.profundidad > j
cazatesoros(i,j) = {
                   { max(cazatesoros(i-1,j) , cazatesoros(i - 1, j - (3 * Ci.profundidad)) + Ci.oro)    si 3 * Ci.profundidad <= j


 Casos base:
    - cazatesoros(i,0) = 0 
    - cazatesoros(0,j) = 0

 Llamada inicial cazatesoros(N,T)

 Se utiliza programacion dinamica descendente debido a que necesitamos reconstruir la solucion pero es importante destacar que para el calculo de la funcion recursiva solo necesitamos
 la fila i-1esima y podriamos reducir el coste en espacio adicional a O(T) utilizando un vector. Se van realizando llamadas recursivas desde la posicion (N,T) hasta llegar a la posicion (0,0) de los casos
 basicos y segun se va desapilando se calculan el resto de valores. De esta manera habra subproblemas que se repitan pero solo seran calculados una unica vez y por lo tanto el coste
 en tiempo sera del orden de O(N*T) al igual que el de espacio adicional debido a la matriz que utilizamos para rellenar con los resultados de los subproblemas. Para la reconstruccion
 de la solucion el espacio adicional es de O(T) por el vector de booleanos que usamos para determinar que cofres seran abiertos.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Cofre {
    int profundidad;
    int oro;
};

int cazatesoros(Matriz<int>& m, int i, int j, const vector<Cofre>& cofres) {
    int& res = m[i][j];
    if (res == -1) {
        if (i == 0 || j == 0)
            res = 0;
        else if (3 * cofres[i - 1].profundidad > j) {
            res = cazatesoros(m, i - 1, j, cofres);
        }
        else
            res = max(cazatesoros(m, i - 1, j, cofres), cazatesoros(m, i - 1, j - (3 * cofres[i - 1].profundidad), cofres) + cofres[i - 1].oro);
    }
    return res;
}

void reconstruccion(const Matriz<int>& m, int i, int j, vector<Cofre>& cofres, vector<bool>& sol, int& cont) {
    while (i > 0 && j > 0) {
        if (m[i][j] != m[i - 1][j]) { // hay que coger este cofre
            sol[i - 1] = true;
            cont++;
            j -= cofres[i - 1].profundidad * 3;
        }
        i--;
    }
}

bool resuelveCaso() {

    int T, N;
    cin >> T;

    if (!std::cin)  // fin de la entrada
        return false;
    cin >> N;

    vector<Cofre> cofres(N);
    for (Cofre& c : cofres)
        cin >> c.profundidad >> c.oro;

    Matriz<int> m(N + 1, T + 1, -1);

    cout << cazatesoros(m, N, T, cofres) << "\n";

    vector<bool> sol(N);
    int cont = 0;
    reconstruccion(m, N, T, cofres, sol, cont);
    cout << cont << "\n";
    for (int i = 0; i < N; i++)
    {
        if (sol[i]) {
            cout << cofres[i].profundidad << " " << cofres[i].oro << "\n";
        }
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
