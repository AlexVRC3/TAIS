
/*@ <authors>
 *
 * Alejandro Vida Ram�rez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
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

struct Tarea {
    int c;
    int f;
    int periodo;
};

bool operator<(const Tarea& t1, const Tarea& t2) {
    return t2.f < t1.f || (t1.f == t2.f && t2.c < t1.c);
}


bool resuelveCaso() {

    int n, m, t;
    cin >> n >> m >> t;

    if (!std::cin)  // fin de la entrada
        return false;
    int c, f, periodo;
    priority_queue<Tarea> pq;
    for (int i = 0; i < n; i++)
    {
        cin >> c >> f;
        pq.push({ c,f,0 });
        
    }
    for (int j = 0; j < m; j++)
    {
        cin >> c >> f >> periodo;
        pq.push({ c,f,periodo });
    }

    bool conflicto = false;
    int finalAnt = 0;
    while (!pq.empty() && !conflicto) {
        Tarea t = pq.top(); pq.pop();
        if (t.c < finalAnt)
            conflicto = true;
        finalAnt = t.f;
        if (t.periodo != 0) {
            t.c += t.periodo;
            t.f += t.periodo;
            pq.push(t);
        }
    }

    if (conflicto)
        cout << "SI";
    else
        cout << "NO";
    cout << "\n";
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
