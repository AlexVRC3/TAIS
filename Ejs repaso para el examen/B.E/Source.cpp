
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

#include "Matriz.h"

/*@ <answer>

lista(i,j) = longitud de la secuencia de canciones comunes mas larga entre las dos listas pudiendo coger las canciones del 1 al i de canciones1 y del 1 al j de canciones2

                { lista(i+1,j+1) + 1                    si canciones1[i] == canciones2[j]
lista(i,j) =    {
                { max(lista(i+1,j), lista(i, j+1))     si canciones1[i] != canciones2[j]

Casos base:
   
    - lista(i,j) = 0 sii i >= N || j >= M

Llamada inicial lista(0,0) siendo N el tamaño de canciones1 y M el tamaño de canciones2

Se utiliza programacion dinamica descendente ya que vamos a necesitar reconstruir la solución. Se crea una matriz inicial de tamaño N-1 * M-1 y se van realizando ese numero de llamadas
recursivas hasta resolver los problemas mas basicos. Mientras se desapilan las llamadas se va generando la solucion final que quedará almacenada en la posicion [N-1][M-1]. El coste en
tiempo de la solucion es del orden de O(N*M) debido a que acota el numero de llamadas recursivas que pueden realizarse aunque realmente se hagan muchas menos y solo generan trabajo
esa vez debido a que ya estaran resueltas en la matriz para las proximas veces que se repitan. El coste en espacio es del orden de O(N*M) debido a la matriz en la que almacenamos
las soluciones de todos los subproblemas.

En cuanto a la reconstruccion de la solucion, partimos de la posicion [0][0] y vamos bajando en diagonal en caso de encontrar coincidencias por lo que en el caso peor podriamos
recorrer una fila y una columna entera pero no llegariamos a recorrer toda la matriz. Por lo expuesto podriamos decir que el coste es de O(N+M).

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
vector<string> leerCanciones() {
    vector<string> canciones;
    string linea, cancion;
    getline(cin, linea);
    stringstream ss(linea);
    while (ss >> cancion) {
        canciones.push_back(cancion);
    }
    return canciones;
}

int lista(Matriz<int>& m, int i, int j, const vector<string>& canciones1, const vector<string>& canciones2) {
    if (i >= m.numfils() || j >= m.numcols()) return 0;
    int& res = m[i][j];
    if (res == -1) {
        if (canciones1[i] == canciones2[j]) {
            res = lista(m, i + 1, j + 1, canciones1, canciones2) + 1;
        }
        else {
            res = max(lista(m, i + 1, j, canciones1, canciones2) , lista(m, i, j + 1, canciones1, canciones2));
        }
    }
    return res;
}

int valida(const Matriz<int>& m, int i, int j) {
    if (i >= m.numfils() || j >= m.numcols()) return 0;
    else return m[i][j];
}

void reconstruir(const vector<string>& canciones1, const vector<string>& canciones2, const Matriz<int>& m, int i, int j, vector<string>& sol) {
    while (i < m.numfils() && j < m.numcols()) {
        if (canciones1[i] == canciones2[j]) {
            sol.push_back(canciones1[i]);
            i++;
            j++;
        }
        else if (valida(m,i,j+1) == m[i][j]) { // avanzamos hacia abajo
            j++;
        }
        else // avanzamos hacia la der
            i++;
    }
}

bool resuelveCaso() {

    // leer los datos de la entrada
    vector<string> canciones1 = leerCanciones();
    vector<string> canciones2 = leerCanciones();

    if (!std::cin)  // fin de la entrada
        return false;
    int N = canciones1.size();
    int M = canciones2.size();
    Matriz<int> m(N , M , -1);
    vector<string> sol;
    lista(m, 0, 0, canciones1, canciones2);
    reconstruir(canciones1, canciones2, m, 0, 0, sol);

    for (string& s : sol)
        cout << s << " ";
    cout << "\n";

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
