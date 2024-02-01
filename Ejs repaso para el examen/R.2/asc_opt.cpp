
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


/*@ <answer>

    formas(i,j) = nº de formas distintas de conseguir la puntuacion j pudiendo realizar todas las tiradas necesarias pudiendo obtener como resultado las caras de la 1 a la i.

                    { formas(i - 1, j)                          si i > j
    formas(i,j) =   {
                    { formas(i - 1, j) + formas(i, j - i)       si i <= j

    Casos base:
        - formas(i,0) = 1 solo hay una unica forma de obtener una puntuacion 0
        - formas(0,j) = 0 no hay manera de obtener la puntuacion j si solo podemos obtener 0 como resultado de las tiradas

    Se utiliza programación dinamica ascendente y se va rellenando la matriz de k + 1 filas y s + 1 columnas de arriba a abajo y de derecha a izquierda. La llamada inicial es
    formas(k,s) y la solución quedará almacenada en la ultima posicion de la matriz. Esta es la version optimizada ya que se puede reducir el coste en espacio adicional utilizando
    solo un vector en vez de una matriz ya que para calcular el resultado de un subproblema en i,j solo necesitamos mirar a la fila de arriba y a la izquierda de la misma (i - 1,j) e (i, j - i)
    El coste en tiempo de este algoritmo es del orden de O(k*s) debido a que se resuelven k*s subproblemas y solo se resuelven una unica vez ya que el resto de las veces ya estan calculados.
    El coste en espacio es O(s) debido al uso del vector para almacenar los resultados de los subproblemas.

    En un instante determinado del calculo de una fila i el vector se vería de esta manera:
     ---------------------------
    |  i    | j |    i  - 1    |
     ---------------------------

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


int resolver(const int k, const int s) {
    vector<int> formas(s + 1, 0);
    formas[0] = 1;
    for (int i = 1; i <= k; i++)
    {
        for (int j = i; j <= s; j++)
        {
            formas[j] += formas[j - i];
        }
    }
    return formas[s];
}

void resuelveCaso() {

    int k, s;
    cin >> k >> s;
    cout << resolver(k, s) << endl;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
