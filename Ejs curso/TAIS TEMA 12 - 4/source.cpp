
/*@ <authors>
 *
 * Alejandro Vida Ram�rez de Arellano TAIS71
 *
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
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


long long int recurrencia2(int N, int M) {
    vector<long long int> v(N, 0);
    v[N - 1] = 1;
    for (int i = N-2; i >= 0; i--)
    {
        int k = 1;
        while (k <= M + 1 && i + k < N) {
            v[i] = (v[i] + v[i + k]) % 1000000007;
            k++;
        }
    }
    return v[0];
}


bool resuelveCaso() {

    int N, M;
    cin >> N >> M;
    if(N == 0 && M == 0)
        return false;

    cout << recurrencia2(N, M) << endl;

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
