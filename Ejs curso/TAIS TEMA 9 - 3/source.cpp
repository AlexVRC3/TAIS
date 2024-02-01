
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

La estrategia voraz considera los voltajes de mayor a menor y a cada uno le asigna el menor valor necesario disponible para que su suma y la del menor alcancen o sobrepasen V.

Haremos una distincion de casos:

CASO 1: la primera componente de la pareja de pilas es igual pero la segunda es distinta.

En la solucion voraz V y en la solucion optima cualquiera O sabemos que la segunda es distinta ya que si no serian la misma soluciom, en este caso sabemos que la pila elegida en V es de menor 
voltaje que la pila elegida en O ya que el algoritmo selecciona siempre la menor pila con la que se alcance V. asi que si sustituimos esa segunda pila por la de V la solucion seguira siendo optima.


CASO 2: la primera componente de la pareja de pilas es distinta pero la segunda es igual.

Esto no puede ocurrir ya que en el algoritmo seleccionamos la pila con mayor voltaje como primer elemento de la pareja. Se propone de nuevo el cambio de la primera componente de la 
pareja en O por la primera componente en V. El resultado es que no empeoramos la solución y sigue siendo optima

Coste O(N log N) por el quicksort dentro de sort y porque resolver y la lectura tienen coste O(N) que es menor

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>



int resolver(vector<int>& pilas, int V) { 
    int ini = 0, fin = pilas.size() - 1;
    int nCoches = 0;
    while (ini < fin) {
        if (pilas[ini] + pilas[fin] >= V) {  // nueva pareja
        
            nCoches++;
            ini++;
        }
        fin--;
    }
    return nCoches;
}
void resuelveCaso() {
    int N, V;
    cin >> N >> V;
    vector<int> pilas(N);
    for (int i = 0; i < N; i++)
    {
        cin >> pilas[i];
    }

    sort(pilas.begin(), pilas.end(), greater<int>()); // O(N log N)

    cout << resolver(pilas,V) << endl;

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
