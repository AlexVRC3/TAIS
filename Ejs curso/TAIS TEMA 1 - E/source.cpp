/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXX) de los autores de la soluci�n.
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

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 TAM_I
 Lo primero es a�adir tam_i a cada nodo cada vez que se a�ade un elemento por la
 izquierda de una ra�z se incrementa uno a esa misma raiz. Si hay que reequilibrar
 el �rbol haciendo las rotaciones hacia izquierda o hacia derecha, y los nodos del sub�rbol
 izquierdo pasen el derecho, se restan dichos nodos a la ra�z del arbol y se suman si es en el
 caso contrario.


 KESIMO
 Lo primero es recorrer el �rbol decidiendo la rama por la que hay que bajar seg�n el n�mero
 acumulado de nodos. En caso de que el n�mero acumulado de nodos m�s los nodos de la ra�z actual
 sea mas peque�o que la posici�n que busco, entonces se baja por la izquierda, y al reves en el
 casocontrario. Hemos encontrado la posici�n cuando se llega a un nodo nullptr o si llego a una raiz
 cuya suma de nodos acumulados mas los nodos izquierdos es la posici�n.


 COSTE -> O(log N)
 Ya que recorre el �rbol por sus ramas, pero nunca entero.
 Se va decidiendo si bajar por la izquierda o la derecha.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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