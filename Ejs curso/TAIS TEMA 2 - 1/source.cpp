
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include <queue>
#include <vector>
#include <algorithm>


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

#define lli long long int

bool resuelveCaso() {

    // leer los datos de la entrada
    int n;
    cin >> n;
    if (n == 0)
        return false;
    priority_queue<lli, vector<lli>, greater<lli>> sumandos;

    int temp;
    for (int i = 0; i < n; i++) {
        std::cin >> temp; 
        sumandos.push(temp);
    }
    
    // resolver el caso posiblemente llamando a otras funciones
    lli suma = 0;
    lli s1, s2;
    while (sumandos.size() > 1) {
        s1 = sumandos.top();
        sumandos.pop();
        s2 = sumandos.top();
        sumandos.pop();

        suma += (s1 + s2);
        sumandos.push(s1 + s2);
    }
    // escribir la solución

    cout << suma << endl;
    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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
