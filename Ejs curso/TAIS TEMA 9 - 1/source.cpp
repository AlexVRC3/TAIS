
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

Coste O(N log N) por el uso de sort para ordenar el vector por los mas occidentales.

La estrategia voraz consiste en considerar los edificios en orden creciente según el punto donde empiezan, y para cada edificio poner un pasadizo al final 
si no esta cubierto por un pasadizo puesto anteriormente.

Sea V la solución voraz y O una solución optima cualquiera distinta a V sabemos que habrá un momento en que las soluciones difieran. En primer lugar, el pasadizo distinto en la solución
óptima debe estar colocado antes del pasadizo en V, ya que si estuviera después habría un edificio sin cubrir y no sería solución.

Se propone sustituir el pasadizo de la solución O por el de la solución V. Sigue siendo solución ya que no deja edificios antes sin cubrir porque el algoritmo voraz lo hubiera colocado antes
y no puede dejar sin cubrir edificios posteriores porque estamos retrasando el pasadizo. Además siguie siendo óptima ya que el numero de pasadizos es el mismo.

Estos cambios pueden repetirse hasta igualar las soluciones y además sabemos que no puede haber mas pasadizos en la solución voraz porque este algoritmo solo pone un pasadizo si quedan
edificios por cubrir, lo cual significaría que la solución optima no estaria cubriendo todos los edificios y por tanto no sería solucion.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Longitud {
    int ini;
    int fin;
};

bool operator<(Longitud l1, Longitud l2) {
    return l1.ini < l2.ini;
}

int resolver(const vector<Longitud>& v) { // O(N)
    int nPasadizos = 1; // Inicialmente hay al menos un pasadizo (el primero)

    int final = v[0].fin;

    for (int i = 1; i < v.size(); i++) {
        if (v[i].ini >= final) {
            nPasadizos++;
            final = v[i].fin;
        }
        else {
            // Si el inicio del edificio actual es menor o igual al final del anterior,
            // actualizamos el final del pasadizo sin incrementar el contador.
            final = min(final, v[i].fin);
        }
    }

    return nPasadizos;
}

bool resuelveCaso() {
    int N;
    int Wi, Ei;

    cin >> N;
    // leer los datos de la entrada

    if (N == 0)  // fin de la entrada
        return false;


    vector<Longitud> v;
    for (int i = 0; i < N; i++)
    {
        cin >> Wi >> Ei;
        v.push_back({ Wi,Ei });
    }

    sort(v.begin(), v.end());

    cout << resolver(v) << endl;

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
