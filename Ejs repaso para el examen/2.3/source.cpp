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

Utilizamos una cola de prioridad de maximos (la definida en la stl) y se ordenan los pacientes por gravedad. De esta manera se atienden
primero a los pacientes con mayor gravedad y en caso de empate a los que mas tiempo lleven esperando. El coste del algoritmo es el orden de
O(N log P) ya que recorremos N eventos y para cada uno de ellos hacemos operaciones de push o pop sobre la cola de pacientes.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

using lli = long long int;

struct Paciente {
    string nombre;
    lli gravedad;
    int tiempoEspera;
};

bool operator<(const Paciente& p1, const Paciente& p2) {
    return p1.gravedad < p2.gravedad || (p1.gravedad == p2.gravedad && p1.tiempoEspera > p2.tiempoEspera);
}


bool resuelveCaso() {

    // leer los datos de la entrada
    int n;
    cin >> n;
    if (n==0)
        return false;
    char aux;
    priority_queue<Paciente> pq;
    for (int i = 0; i < n; i++) 
    {
        cin >> aux;
        if (aux == 'I') {
            Paciente p;
            cin >> p.nombre >> p.gravedad;
            p.tiempoEspera = i;
            pq.push(p); // O(log P)
        }
        else {
            Paciente p = pq.top(); pq.pop(); // O(log P)
            cout << p.nombre << "\n";
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
