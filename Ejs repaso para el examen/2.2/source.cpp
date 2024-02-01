
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

Utilizamos una cola de prioridad de minimos en las que los elementos son los usuarios. Los usuarios se ordenan por el momento en el que les toca recibir informacion que se va actualizando
cada vez que reciben la informacion con la periocidad con la que desean hacerlo. Por ejemplo si el usuario 1234 quiere recibir mensajes cada 200 ut. Recibira en el momento 200 y luego lo hara en el 400.. 600 etc

El coste de la solucion es del orden de O(N log N + K log N) ya que la lectura de datos e insercion en la cola es N log N y el bucle de la solucion realiza K vueltas y en cada vuelta
se realizan operaciones de coste log N son pop y push.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Usuario {
    int momento;
    int id;
    int period;
};

bool operator<(const Usuario& u1, const Usuario& u2) {
    return u2.momento < u1.momento || 
        (u1.momento == u2.momento && u2.id < u1.id);
}


bool resuelveCaso() {

    int nUsuarios;
    cin >> nUsuarios;
    if (nUsuarios == 0)
        return false;
    int id;
    int period;
    priority_queue<Usuario> pq;
    for (int i = 0; i < nUsuarios; i++)
    {
        cin >> id >> period;
        pq.push({ period,id,period }); // O(log N)

    }
    int k;
    cin >> k;

    for (int i = 0; i < k; i++)
    {
        Usuario u = pq.top(); pq.pop();
        cout << u.id << "\n";
        u.momento += u.period;
        pq.push(u);
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
