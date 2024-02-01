
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
#include <algorithm>

/*@ <answer>

Ci: precio del concierto i
Ni: numero de grupos del concierto i

concierto(i,j) = numero de grupos a los que sergio puede ir a ver pudiendo ir a los conciertos del 1 al i y teniendo un presupuesto de j

                 {  concierto(i-1,j)                                         si Ci > j
concierto(i,j) = {
                 {  max(concierto(i-1,j), concierto(i - 1, j - Ci) + Ni)     si Ci <= j

Casos base:

    concierto(i,0) = 0 si no hay presupuesto
    concierto(0,j) = 0 si no hay grupos a los que ver

Se utiliza programación dinamica ascendente y se va rellenando la matriz de tamaño N+1 por P+1. De esta manera la solución quedará almacenada en la ultima posicion de la matriz
[N][P]. Como para calcular la posicion i,j solo necesitamos la fila anterior y la actual podemos reducir el espacio adicional de una matriz a un vector en el cual iremos rellenando
de izquierda a derecha por lo que en un momento dado del calculo de la fila i el vector se vería asi.
    --------------------------
    |  fila i | j | fila i - 1 |
    ---------------------------

El coste en tiempo es del orden de O(N*P) ya que recorremos la matriz entera y el coste en espacio adicional es del orden de O(P) debido al uso del vector.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Festival {
    int nGrupos;
    int precio;
};

//int resolver(const vector<Festival> &festivales, int P){
//    int N = festivales.size();
//    Matriz<int> m(N + 1, P + 1, 0);
//    for (int i = 1; i <= N; i++)
//       for (int j = 1; j <= P; j++)
//       {
//           if (festivales[i - 1].precio > j) {
//               m[i][j] = m[i - 1][j];
//           }
//           else {
//               m[i][j] = max(m[i - 1][j], m[i - 1][j - festivales[i - 1].precio] + festivales[i - 1].nGrupos);
//           }
//       }
//
//    return m[N][P];
//}

int resolver(const vector<Festival>& festivales, int P) {
    int N = festivales.size();
    vector<int> m(P + 1, 0);
    for (int i = 1; i <= N; i++)
        for (int j = P; j >= 0; j--)
        {
            if(festivales[i-1].precio <= j)
             m[j] = max(m[j], m[j - festivales[i - 1].precio] + festivales[i - 1].nGrupos);
        }

    return m[P];
}


bool resuelveCaso() {

    // leer los datos de la entrada
    int P, N;
    cin >> P >> N;

    if (!std::cin)  // fin de la entrada
        return false;
    vector<Festival> festivales(N);
    for (Festival& f : festivales)
        cin >> f.nGrupos >> f.precio;

    cout << resolver(festivales, P) << "\n";

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
