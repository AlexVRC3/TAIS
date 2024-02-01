
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;


/*@ <answer>

 Utilizo una cola de prioridad de minimos en las cuales guardamos a los equipos representados por el numero de seguidores. Para realizar un enfrentamiento sacamos a los dos primeros de la cola
 y de esta manera siempre se enfrentan los dos equipos con menos seguidores asegurando que tenemos que repartir el menor numero de gorras por enfrentamiento. El coste del algoritmo es del orden de
 O(N log N) ya que en la lectura recorremos N equipos y hacemos push sobre la cola de prioridad que tiene coste log N.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

using lli = long long int;

bool resuelveCaso() {

    int N;
    // leer los datos de la entrada
    cin >> N;
    if (N == 0)
        return false;
    priority_queue<lli, vector<lli>, greater<lli>> equipos; // Cola de prioridad de minimos
    lli seguidores;
    for (int i = 0; i < N; i++)
    {
        cin >> seguidores;
        equipos.push(seguidores);
    }
    lli gorrasTotales = 0;
    while (equipos.size() > 1) {
        
        lli equipo1 = equipos.top();
        equipos.pop();
        lli equipo2 = equipos.top();
        equipos.pop();
        gorrasTotales += equipo1 + equipo2;
        equipos.push(equipo1 + equipo2); // Al perder se suman los seguidores de un equipo a otro
        
    }
    cout << gorrasTotales << "\n";

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
