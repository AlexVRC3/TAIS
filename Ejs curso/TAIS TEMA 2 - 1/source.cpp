
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXX) de los autores de la soluci�n.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include <queue>
#include <vector>
#include <algorithm>


/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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
    // escribir la soluci�n

    cout << suma << endl;
    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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
