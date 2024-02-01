
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
using namespace std;


/*@ <answer>

La solucion consiste en tener un vector de tamaño N de pilas de comics para poder acceder a la parte superior de cada monton. Utilizo una cola de prioridad para saber que comics
se van a ir eligiendo en cada turno y de esta manera poder saber en que posicion de la cola hay que colocarse para coger el de id menor. El coste de la solucion es O(N * K log N)
debido a que en la lectura se leen K comics de N pilas en total y en la resolucion del ejercicio se hacen operaciones de push y pop sobre la cola de prioridad que tiene tamaño
N a lo sumo y por ello el O(log N).

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Comic {
    int pila;
    int id;
};

bool operator<(const Comic& c1, const Comic& c2) {
    return c2.id < c1.id;
}


bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    int K;
    int id;
    vector<stack<Comic>> pilas(N); 
    int min = INT_MAX;
    for (int i = 0; i < N; i++)
    {
        cin >> K;
        for (int j = 0; j < K; j++)
        {
            cin >> id;
            pilas[i].push({ i,id }); //O(1)
            if (id < min)
                min = id;
        }
    }
    priority_queue<Comic> primeros; // O(N) porque puede contener a la vez como mucho 1 comic de cada pila
    for (int i = 0; i < N; i++)
    {
        primeros.push(pilas[i].top()); // O(log N)
        pilas[i].pop(); // O(1)
    }
    int posCola = 1;
    while (!primeros.empty() && primeros.top().id != min) {
        Comic c = primeros.top();
        primeros.pop(); // O(log N)
        if (!pilas[c.pila].empty()) {
            primeros.push(pilas[c.pila].top());
            pilas[c.pila].pop(); //O(1)
        }
       
        posCola++;
    }

    cout << posCola << endl;

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
