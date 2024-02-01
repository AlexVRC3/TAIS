/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXX) de los autores de la solución.
 *
 * Gabriel Torres Martin TAIS64
 * Alejando Vida Ramirez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include "TreeSet_AVL.h"

using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 TAM_I
 Lo primero es añadir tam_i a cada nodo cada vez que se añade un elemento por la
 izquierda de una raíz se incrementa uno a esa misma raiz. Si hay que reequilibrar
 el árbol haciendo las rotaciones hacia izquierda o hacia derecha, y los nodos del subárbol
 izquierdo pasen el derecho, se restan dichos nodos a la raíz del arbol y se suman si es en el
 caso contrario.


 KESIMO
 Lo primero es recorrer el árbol decidiendo la rama por la que hay que bajar según el número
 acumulado de nodos. En caso de que el número acumulado de nodos más los nodos de la raíz actual
 sea mas pequeño que la posición que busco, entonces se baja por la izquierda, y al reves en el
 casocontrario. Hemos encontrado la posición cuando se llega a un nodo nullptr o si llego a una raiz
 cuya suma de nodos acumulados mas los nodos izquierdos es la posición.


 COSTE -> O(log N)
 Ya que recorre el árbol por sus ramas, pero nunca entero.
 Se va decidiendo si bajar por la izquierda o la derecha.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

    int N, elem;
    cin >> N;
    if (N == 0)
        return false;

    Set<int> arbol;
    for (int i = 0; i < N; ++i) {
        cin >> elem;
        arbol.insert(elem);
    }

    int M, k;
    cin >> M;
    for (int i = 0; i < M; ++i) {
        cin >> k;
        try {
            cout << arbol.kesimo(k) << "\n";
        }
        catch (std::out_of_range& e) {
            cout << "??\n";
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