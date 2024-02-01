
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;

#include "PriorityQueue.h"

/*@ <answer>

Se utiliza una cola de prioridad de minimos en la cual los elementos son los numeros a sumar. Cogemos los dos primeros numeros de la cola de prioridad y los sumamos para calcular el esfuerzo. Una
vez calculado lo insertamos en la cola de prioridad de manera que siempre estarán arriba los mas pequeños. Esto se repite hasta realizar N-1 sumas.

El coste del algoritmo es del orden de O(N log N) ya que damos N - 1 vueltas y en cada vuelta hacemos operaciones sobre la cola que tienen coste log N. N es el numero de sumandos

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int resolver(const vector<long long int>& v) {
    PriorityQueue<long long int> pq(v);
    long long int esfuerzo = 0, esfuerzoTotal = 0;
    for (int i = 0; i < v.size() - 1; i++)
    {
        long long int primero = pq.top();
        pq.pop();
        long long int segundo = pq.top();
        pq.pop();
        esfuerzo = primero + segundo;
        esfuerzoTotal += esfuerzo;
        pq.push(esfuerzo);
        esfuerzo = 0;
    }
    return esfuerzoTotal;
}

bool resuelveCaso() {

    int N;
    cin >> N;
    if (N == 0)
        return false;

    vector<long long int> v(N);
    for (int i = 0; i < N; i++)
    {
        cin >> v[i];
    }

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
