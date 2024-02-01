
/*@ <authors>
 *
 * Alejandro Vida TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;


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

struct paciente {
    string nombre;
    lli gravedad;
    int tiempoEsperado;
};

bool operator<(paciente const& a, paciente const& b) {
    return a.gravedad < b.gravedad ||
        (a.gravedad == b.gravedad && a.tiempoEsperado > b.tiempoEsperado);
}

bool resuelveCaso() {

    // leer los datos de la entrada
    lli nEventos;
    cin >> nEventos;
    if (nEventos == 0)
        return false;

    priority_queue<paciente> pq;
    char aux;
    for (lli i = 0; i < nEventos; i++)
    {
        cin >> aux;
        if (aux == 'I') { // Ingreso
            paciente p;
            cin >> p.nombre;
            cin >> p.gravedad;
            p.tiempoEsperado = i;
            pq.push({p});
        }
        else if(aux == 'A'){ // Atencion
            cout << pq.top().nombre << endl;
            pq.pop();
        }
    }

    std::cout << "---" << endl;


    // resolver el caso posiblemente llamando a otras funciones

    // escribir la soluci�n

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
